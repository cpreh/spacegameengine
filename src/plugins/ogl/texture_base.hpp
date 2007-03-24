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


#ifndef SGE_OGL_TEXTURE_BASE_HPP_INCLUDED
#define SGE_OGL_TEXTURE_BASE_HPP_INCLUDED

#include "common.hpp"

namespace sge
{
namespace ogl
{

class texture_base {
public:
	GLenum type() const;
	virtual void bind_me() const = 0;
	virtual GLuint id() const = 0;
	virtual ~texture_base() {}
protected:
	texture_base(const GLenum type);
private:
	GLenum _type;
};

}
}

#endif
