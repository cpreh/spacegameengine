/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_GLSL_UNIFORM_TYPE_HPP_INCLUDED
#define SGE_OPENGL_GLSL_UNIFORM_TYPE_HPP_INCLUDED

#include <sge/opengl/glsl/uniform/type_fwd.hpp>
#include <sge/opengl/glsl/uniform/element_type.hpp>
#include <sge/opengl/glsl/uniform/size_type.hpp>

namespace sge
{
namespace opengl
{
namespace glsl
{
namespace uniform
{

class type
{
public:
	type(
		uniform::element_type::type,
		uniform::size_type elements
	);

	uniform::element_type::type
	element_type() const;

	uniform::size_type
	elements() const;
private:
	uniform::element_type::type type_;

	uniform::size_type elements_;
};

}
}
}
}

#endif
