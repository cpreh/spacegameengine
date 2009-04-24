/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_OPENGL_GLSL_ATTRIBUTE_VARIABLE_HPP_INCLUDED
#define SGE_OPENGL_GLSL_ATTRIBUTE_VARIABLE_HPP_INCLUDED

#include "type.hpp"
#include "../traits.hpp"
#include "../../common.hpp"
#include <sge/renderer/glsl/attribute/variable.hpp>
#include <sge/renderer/glsl/string.hpp>

namespace sge
{
namespace ogl
{
namespace glsl
{
namespace attribute
{

template<bool Native>
class variable : public renderer::glsl::attribute::variable {
public:
	typedef typename traits<Native>::handle handle;

	variable(
		handle program,
		renderer::glsl::string const &name);
	
	renderer::glsl::attribute::value const get() const;
	void set(
		renderer::glsl::attribute::value const &);
private:
	GLint const location;
	type::type  stored_type;
};

}
}
}
}

#endif
