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


#include "../type.hpp"
#include "../element_type.hpp"
#include "../size_type.hpp"

sge::opengl::glsl::uniform::type::type(
	uniform::element_type::type const _type,
	size_type const _elements
)
:
	type_(_type),
	elements_(_elements)
{}

sge::opengl::glsl::uniform::element_type::type
sge::opengl::glsl::uniform::type::element_type() const
{
	return type_;
}

sge::opengl::glsl::uniform::size_type
sge::opengl::glsl::uniform::type::elements() const
{
	return elements_;
}
