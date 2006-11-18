/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OGL_BASIC_TEXTURE_HPP_INCLUDED
#define SGE_OGL_BASIC_TEXTURE_HPP_INCLUDED

#include "./common.hpp"
#include "./texture_base.hpp"
#include "./error.hpp"
#include <stdexcept>

namespace sge
{
namespace ogl
{

template<typename Base, GLenum Type> class basic_texture : public Base, public texture_base {
protected:
	static void tex_parameter_i(const GLenum type, const GLenum name, const GLint param)
	{
		glTexParameteri(type,name,param);
		if(is_error())
			throw std::runtime_error("glTexParamteri() failed!");
	}
	void bind_me() const
	{
		glBindTexture(Type,id);
		if(is_error())
			throw std::runtime_error("glBindTexture() failed!");
	}
public:
	typedef typename Base::value_type value_type;
	typedef typename Base::size_type size_type;
	typedef typename Base::difference_type difference_type;
	typedef typename Base::pointer pointer;
	typedef typename Base::const_pointer const_pointer;

	basic_texture(const unsigned mipmaps, const resource_flag_t _flags)
	 : texture_base(Type), mipmaps(mipmaps), _flags(_flags)
	{
		glGenTextures(1,&id);
		if(is_error())
			throw std::runtime_error("glGenTextures() failed!");
		bind_me();
		tex_parameter_i(Type,GL_TEXTURE_MAX_LEVEL,mipmaps);
		tex_parameter_i(Type,GL_GENERATE_MIPMAP,mipmaps > 1 ? GL_TRUE : GL_FALSE);
	}
	virtual size_type size() const = 0;
	~basic_texture()
	{
		glDeleteTextures(1,&id);
	}
	void restore(){}
	resource_flag_t flags() const { return _flags; }
private:
	unsigned mipmaps;
	resource_flag_t _flags;
};

}
}

#endif

