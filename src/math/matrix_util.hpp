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


#ifndef SGE_MATH_MATRIX_UTIL_HPP_INCLUDED
#define SGE_MATH_MATRIX_UTIL_HPP_INCLUDED

#include "matrix.hpp"
#include "vector.hpp"
#include "../types.hpp"

namespace sge
{
namespace math
{

space_matrix matrix_translation(
	const math::basic_vector<space_unit,3>& v);

space_matrix matrix_translation(
	const space_unit x,
	const space_unit y,
	const space_unit z);

space_matrix matrix_scaling(
	const math::basic_vector<space_unit,3>& v);

space_matrix matrix_scaling(
	const space_unit x,
	const space_unit y,
	const space_unit z);

space_matrix matrix_perspective(
	const space_unit aspect,
	const space_unit fov,
	const space_unit near,
	const space_unit far);

space_matrix matrix_orthogonal_xy();

space_matrix matrix_rotation_z(const space_unit angle);

space_matrix matrix_rotation_y(const space_unit angle);

space_matrix matrix_rotation_x(const space_unit angle);

space_matrix matrix_identity();

space_matrix matrix_orthogonal_xy(
	const space_unit left,
	const space_unit right,
	const space_unit top,
	const space_unit bottom,
	const space_unit near,
	const space_unit far);
}
}

#endif
