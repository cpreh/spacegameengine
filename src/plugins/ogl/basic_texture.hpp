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


#ifndef SGE_OGL_BASIC_TEXTURE_HPP_INCLUDED
#define SGE_OGL_BASIC_TEXTURE_HPP_INCLUDED

#include <iostream>
#include "../../exception.hpp"
#include "common.hpp"
#include "conversion.hpp"
#include "texture_base.hpp"
#include "error.hpp"

namespace sge
{
namespace ogl
{

template<typename Base, GLenum Type> class basic_texture : public Base, public texture_base {
private:
	static void tex_parameter_i(const GLenum name, const GLint param)
	{
		glTexParameteri(Type,name,param);
		if(is_error())
			throw exception("glTexParamteri() failed!");
	}
protected:
	void bind_me() const
	{
		glBindTexture(Type,id());
		if(is_error())
			throw exception("glBindTexture() failed!");
	}

	void set_my_filter() const
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

	GLuint id() const
	{
		return _id;
	}

	const filter_args& filter() const
	{
		return _filter;
	}
public:
	typedef typename Base::value_type value_type;
	typedef typename Base::size_type size_type;
	typedef typename Base::difference_type difference_type;
	typedef typename Base::pointer pointer;
	typedef typename Base::const_pointer const_pointer;

	basic_texture(const filter_args& _filter, const resource_flag_t _flags)
	 : texture_base(Type), _filter(_filter), _flags(_flags)
	{
		glGenTextures(1,&_id);
		if(is_error())
			throw exception("glGenTextures() failed!");
	}
	
	virtual size_type size() const = 0;
	
	~basic_texture()
	{
		glDeleteTextures(1,&_id);
	}

	resource_flag_t flags() const
	{
		return _flags;
	}

	void filter(const filter_args& nfilter)
	{
		// TODO: what we do with mipmapping here?
		_filter = nfilter;
		bind_me();
		set_my_filter();
	}
private:
	filter_args _filter;
	resource_flag_t _flags;
	GLuint _id;
};

}
}

#endif

