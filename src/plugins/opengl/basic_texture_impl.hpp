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

#include <iostream>
#include "../../exception.hpp"
#include "common.hpp"
#include "conversion.hpp"
#include "error.hpp"

template<typename Base, GLenum Type>
void sge::ogl::basic_texture<Base, Type>::tex_parameter_i(const GLenum name, const GLint param)
{
	glTexParameteri(Type,name,param);
	if(is_error())
		throw exception("glTexParamteri() failed!");
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
	return _id;
}

template<typename Base, GLenum Type>
const sge::filter_args& sge::ogl::basic_texture<Base, Type>::filter() const
{
	return _filter;
}

template<typename Base, GLenum Type>
sge::ogl::basic_texture<Base, Type>::basic_texture(const filter_args& _filter, const resource_flag_t _flags)
 : texture_base(Type),
   _filter(_filter),
   _flags(_flags)
{
	glGenTextures(1,&_id);
	if(is_error())
		throw exception("glGenTextures() failed!");
}


template<typename Base, GLenum Type>
sge::ogl::basic_texture<Base, Type>::~basic_texture()
{
	glDeleteTextures(1,&_id);
}

template<typename Base, GLenum Type>
sge::resource_flag_t sge::ogl::basic_texture<Base, Type>::flags() const
{
	return _flags;
}

#endif
