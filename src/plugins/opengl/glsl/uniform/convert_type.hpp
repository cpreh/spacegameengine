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


#ifndef SGE_OPENGL_GLSL_UNIFORM_CONVERT_TYPE_HPP_INCLUDED
#define SGE_OPENGL_GLSL_UNIFORM_CONVERT_TYPE_HPP_INCLUDED

#include "element_type.hpp"
#include <sge/renderer/glsl/uniform/int_value_type.hpp>
#include <sge/renderer/glsl/uniform/float_value_type.hpp>

namespace sge
{
namespace opengl
{
namespace glsl
{
namespace uniform
{

template<
	typename Dest
>
Dest
convert_type(
	element_type::type
);

template<>
sge::renderer::glsl::uniform::int_value_type::type
convert_type(
	element_type::type
);

template<>
sge::renderer::glsl::uniform::float_value_type::type
convert_type(
	element_type::type
);

}
}
}
}

#endif
