/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENGL_BASIC_TEXTURE_IMPL_HPP_INCLUDED
#define SGE_OPENGL_BASIC_TEXTURE_IMPL_HPP_INCLUDED

#include <algorithm>
#include <iostream>
#include <ostream>
#include "../../exception.hpp"
#include "common.hpp"
#include "conversion.hpp"
#include "error.hpp"

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::tex_parameter_i(const GLenum name, const GLint param)
{
	glTexParameteri(Type, name, param);
	if(is_error())
		throw exception("glTexParamteri() failed!");
}

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::check_lock() const
{
	if(!cur_buffer)
		throw exception("ogl pbo used which is not locked!");
}

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::bind_me() const
{
	glBindTexture(Type,id());
	if(is_error())
		throw exception("glBindTexture() failed!");
}

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::set_my_filter() const
{
	tex_parameter_i(GL_TEXTURE_MIN_FILTER, convert_cast<GLenum>(filter().min_filter));
	tex_parameter_i(GL_TEXTURE_MAG_FILTER, convert_cast<GLenum>(filter().mag_filter));
	if(filter().anisotropy_level != 0)
	{
#if GL_EXT_texture_filter_anisotropic
		try
		{
			tex_parameter_i(GL_TEXTURE_MAX_ANISOTROPY_EXT, filter().anisotropy_level);
		}
		catch(const exception&)
		{
			std::cerr << "Warning: anisotropy level " << filter().anisotropy_level << " not supported!\n";
		}
#else
		std::cerr << "Warning: anisotropic filtering is not supported!\n";
#endif
	}
}


template<typename Base, GLenum Type>
GLuint sge::ogl::basic_texture<Base, Type>::id() const
{
	return id_;
}

template<typename Base, GLenum Type>
const sge::filter_args& sge::ogl::basic_texture<Base, Type>::filter() const
{
	return filter_;
}

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::do_lock(const lock_flag_t lmode)
{
	if(cur_buffer)
		throw exception("ogl::basic_texture is already locked!");

	if(lmode == lock_flags::writeonly || lmode == lock_flags::readwrite)
	{
		unpack_buffer.reset(new pixel_unpack_buffer(size(), flags(), 0));
		unpack_buffer->lock(lmode);
		cur_buffer = unpack_buffer.get();
	}
	else if(lmode == lock_flags::readonly || lmode == lock_flags::readwrite)
	{
		pack_buffer.reset(new pixel_pack_buffer(size(), flags(), 0));
		pack_buffer->lock(lmode);
		cur_buffer = pack_buffer.get();
	}

	if(lmode == lock_flags::readwrite)
	{
		std::copy(pack_buffer->begin(), pack_buffer->end(), unpack_buffer->data());
		pack_buffer->unlock();
		pack_buffer.reset();
		cur_buffer = unpack_buffer.get();
	}
}

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::do_unlock()
{
	if(!cur_buffer)
		throw exception("ogl::basic_texture is not locked!");

	cur_buffer->unlock();
	pack_buffer.reset();
	unpack_buffer.reset();
	cur_buffer = 0;
}

template<typename Base, GLenum Type>
sge::ogl::basic_texture<Base, Type>::basic_texture(const filter_args& filter_,
                                                   const resource_flag_t flags_)
 : texture_base(Type),
   filter_(filter_),
   flags_(flags_),
   cur_buffer(0)
{
	glGenTextures(1, &id_);
	if(is_error())
		throw exception("glGenTextures() failed!");
}


template<typename Base, GLenum Type>
sge::ogl::basic_texture<Base, Type>::~basic_texture()
{
	glDeleteTextures(1, &id_);
}

template<typename Base, GLenum Type>
sge::resource_flag_t sge::ogl::basic_texture<Base, Type>::flags() const
{
	return flags_;
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_texture<Base, Type>::pointer sge::ogl::basic_texture<Base, Type>::data()
{
	check_lock();
	return cur_buffer->data();
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_texture<Base, Type>::const_pointer sge::ogl::basic_texture<Base, Type>::data() const
{
	check_lock();
	return cur_buffer->data();
}

#endif
