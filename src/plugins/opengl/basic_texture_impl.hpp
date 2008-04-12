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

#include "common.hpp"
#include "error.hpp"
#include "texture_functions.hpp"
#include <sge/exception.hpp>
#include <cassert>
#include <algorithm>

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::check_lock() const
{
	if(!cur_buffer)
		throw exception(SGE_TEXT("ogl pbo used which is not locked!"));
}

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::bind_me() const
{
	bind_texture(Type, id());
}

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::set_my_filter() const
{
	set_texture_filter(Type, filter());
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
		throw exception(SGE_TEXT("ogl::basic_texture::do_lock(): texture is already locked!"));

	lock_mode_ = lmode;

	if(lock_flag_write(lmode))
	{
		unpack_buffer.reset(
			new pixel_unpack_buffer(
				size(),
				flags(),
				0));
		cur_buffer = unpack_buffer.get();
	}

	if(lock_flag_read(lmode))
	{
		pack_buffer.reset(
			new pixel_pack_buffer(
				size(),
				flags(),
				0));
		cur_buffer = pack_buffer.get();
	}

	assert(cur_buffer);
}

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::post_lock()
{
	if(!cur_buffer)
		throw exception(SGE_TEXT("ogl::basic_texture::post_lock(): texture is not locked!"));

	cur_buffer->lock(lock_mode());
}

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::pre_unlock()
{
	if(!cur_buffer)
		throw exception(SGE_TEXT("ogl::basic_texture::pre_unlock(): texture is not locked!"));
	if(lock_mode() == lock_flags::readwrite)
	{
		assert(unpack_buffer);

		unpack_buffer->lock(lock_mode());
		std::copy(pack_buffer->begin(), pack_buffer->end(), unpack_buffer->data());
		pack_buffer->unlock();
		pack_buffer.reset();
		cur_buffer = unpack_buffer.get();
	}
	
	cur_buffer->unlock();
}

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::do_unlock()
{
	if(!cur_buffer)
		throw exception(SGE_TEXT("ogl::basic_texture::do_unlock(): texture is not locked!"));

	if(pack_buffer)
		pack_buffer->unbind();
	if(unpack_buffer)
		unpack_buffer->unbind();

	pack_buffer.reset();
	unpack_buffer.reset();
	cur_buffer = 0;
}

template<typename Base, GLenum Type>
sge::lock_flag_t sge::ogl::basic_texture<Base, Type>::lock_mode() const
{
	return lock_mode_;
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_texture<Base, Type>::pointer sge::ogl::basic_texture<Base, Type>::read_buffer() const
{
	if(!pack_buffer)
		throw exception(SGE_TEXT("pack_buffer not set in basic_texture::read_buffer()!"));
	return pack_buffer->buffer_offset(0);
}

template<typename Base, GLenum Type>
typename sge::ogl::basic_texture<Base, Type>::pointer sge::ogl::basic_texture<Base, Type>::write_buffer() const
{
	if(!unpack_buffer)
		throw exception(SGE_TEXT("unpack_buffer not set in basic_texture::write_buffer()!"));

	return unpack_buffer->buffer_offset(0);
}

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::pre_setdata() const
{
	bind_me();
	set_my_filter();
}

template<typename Base, GLenum Type>
sge::ogl::basic_texture<Base, Type>::basic_texture(const filter_args& filter_,
                                                   const resource_flag_t flags_)
 : texture_base(Type),
   filter_(filter_),
   flags_(flags_),
   id_(gen_texture()),
   cur_buffer(0)
{}


template<typename Base, GLenum Type>
sge::ogl::basic_texture<Base, Type>::~basic_texture()
{
	delete_texture(id());
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
