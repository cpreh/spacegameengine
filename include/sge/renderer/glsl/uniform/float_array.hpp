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


#ifndef SGE_RENDERER_GLSL_UNIFORM_FLOAT_ARRAY_HPP_INCLUDED
#define SGE_RENDERER_GLSL_UNIFORM_FLOAT_ARRAY_HPP_INCLUDED

#include <sge/renderer/glsl/uniform/float_array_type.hpp>
#include <sge/renderer/glsl/float_type.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace renderer
{
namespace glsl
{
namespace uniform
{

class float_array {
public:
	typedef float_type const *const_pointer;

	SGE_SYMBOL float_array(
		const_pointer data,
		float_array_type::type);

	SGE_SYMBOL const_pointer
	data() const;

	SGE_SYMBOL float_array_type::type
	type() const;
private:
	const_pointer data_;
	float_array_type::type type_;
};

}
}
}
}

#endif
