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
#include "../su.hpp"
#include "../export.hpp"

namespace sge
{
namespace math
{

SGE_SYMBOL space_matrix matrix_translation(
	const math::basic_vector<space_unit,3>& v);

SGE_SYMBOL space_matrix matrix_translation(
	space_unit x,
	space_unit y,
	space_unit z);

SGE_SYMBOL space_matrix matrix_scaling(
	const math::basic_vector<space_unit,3>& v);

SGE_SYMBOL space_matrix matrix_scaling(
	space_unit x,
	space_unit y,
	space_unit z);

SGE_SYMBOL space_matrix matrix_perspective(
	space_unit aspect,
	space_unit fov,
	space_unit near,
	space_unit far);

SGE_SYMBOL space_matrix matrix_orthogonal_xy();

SGE_SYMBOL basic_matrix<space_unit,2,2> matrix_rotation_2d(
	space_unit angle);

SGE_SYMBOL space_matrix matrix_rotation_z(
	space_unit angle);

SGE_SYMBOL space_matrix matrix_rotation_y(
	space_unit angle);

SGE_SYMBOL space_matrix matrix_rotation_x(
	space_unit angle);

SGE_SYMBOL space_matrix matrix_identity();

SGE_SYMBOL space_matrix matrix_orthogonal_xy(
	space_unit left,
	space_unit right,
	space_unit top,
	space_unit bottom,
	space_unit near,
	space_unit far);

SGE_SYMBOL space_matrix matrix_orthogonal_xy(
	space_unit left,
	space_unit right,
	space_unit top,
	space_unit bottom);
}
}

#endif
