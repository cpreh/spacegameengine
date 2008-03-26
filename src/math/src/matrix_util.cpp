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


#include "../matrix_util.hpp"
#include "../matrix_impl.hpp"
#include <cmath>

sge::math::space_matrix sge::math::matrix_translation(
	const basic_vector<space_unit,3>& v)
{
	return space_matrix
	       (1, 0, 0, v.x(),
	        0, 1, 0, v.y(),
	        0, 0, 1, v.z(),
	        0, 0, 0, 1);

}

sge::math::space_matrix sge::math::matrix_translation(
	const space_unit x,
	const space_unit y,
	const space_unit z)
{
	return matrix_translation(math::basic_vector<space_unit,3>(x,y,z));
}

sge::math::space_matrix sge::math::matrix_scaling(
	const basic_vector<space_unit,3>& v)
{
	return space_matrix
	       (v.x(),     0,     0, 0,
	            0, v.y(),     0, 0,
	            0,     0, v.z(), 0,
	            0,     0,     0, 1);
}

sge::math::space_matrix sge::math::matrix_scaling(
	const space_unit x,
	const space_unit y,
	const space_unit z)
{
	return matrix_scaling(math::basic_vector<space_unit,3>(x,y,z));
}

#undef near
#undef far

sge::math::space_matrix sge::math::matrix_perspective(
	const space_unit aspect,
	const space_unit fov,
	const space_unit near,
	const space_unit far)
{
	if(compare(far, near))
		throw exception(SGE_TEXT("matrix_perspective(): far may not be near!"));
	if(almost_zero(near))
		throw exception(SGE_TEXT("matrix_perspective(): near must not be 0!"));
	const space_unit h = static_cast<space_unit>(1) / std::tan(fov / static_cast<space_unit>(2)),
	                 w = h / aspect,
	                 q = (far + near) / (far - near);
	return space_matrix
	       (w, 0,                     0, 0,
	        0, h,                     0, 0,
	        0, 0,                     q, 1,
	        0, 0, 2*far*near/(near-far), 0);
}

sge::math::space_matrix sge::math::matrix_orthogonal_xy()
{
	return space_matrix
	       (1,0,0,0,
	        0,1,0,0,
	        0,0,0,0,
	        0,0,0,1);
}

sge::math::space_matrix sge::math::matrix_rotation_z(const space_unit angle)
{
	const space_unit sinx = std::sin(angle),
	                 cosx = std::cos(angle);
	return space_matrix
	       (cosx, -sinx, 0, 0,
	        sinx,  cosx, 0, 0,
	        0,     0,    1, 0,
	        0,     0,    0, 1);
}

sge::math::space_matrix sge::math::matrix_rotation_y(const space_unit angle)
{
	const space_unit sinx = std::sin(angle),
	                 cosx = std::cos(angle);
	return space_matrix
	       (cosx, 0,-sinx, 0,
	        0,  1, 0, 0,
	        sinx,     0,    cosx, 0,
	        0,     0,    0, 1);
}

sge::math::space_matrix sge::math::matrix_rotation_x(const space_unit angle)
{
	const space_unit sinx = std::sin(angle),
	                 cosx = std::cos(angle);
	return space_matrix
	       (1,      0,    0, 0,
	        0,  cosx, -sinx, 0,
	        0,  sinx,  cosx, 0,
	        0,     0,     0, 1);
}

sge::math::space_matrix sge::math::matrix_identity()
{
	return space_matrix
	       (1,0,0,0,
	        0,1,0,0,
	        0,0,1,0,
	        0,0,0,1);
}

sge::math::space_matrix
sge::math::matrix_orthogonal_xy(
	const space_unit left,
	const space_unit right,
	const space_unit top,
	const space_unit bottom,
	const space_unit near,
	const space_unit far)
{
	return space_matrix
	       (2/(right - left), 0, 0, -(right+left)/(right-left),
	        0, 2/(top - bottom), 0, -(top+bottom)/(top-bottom),
	        0, 0, (-2)/(far - near),-(far+near)/(far-near),
	        0, 0, 0, 1);
}
