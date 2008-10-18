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


#include <sge/math//matrix_util.hpp>
#include <sge/math//matrix_impl.hpp>
#include <sge/su.hpp>
#include <cmath>

sge::math::space_matrix const
sge::math::matrix_translation(
	basic_vector<space_unit, 3> const &v)
{
	return space_matrix
	       (su(1), su(0), su(0), v.x(),
	        su(0), su(1), su(0), v.y(),
	        su(0), su(0), su(1), v.z(),
	        su(0), su(0), su(0), su(1));

}

sge::math::space_matrix const
sge::math::matrix_translation(
	space_unit const x,
	space_unit const y,
	space_unit const z)
{
	return matrix_translation(
		basic_vector<space_unit, 3>(
			x,
			y,
			z));
}

sge::math::space_matrix const
sge::math::matrix_scaling(
	basic_vector<space_unit, 3> const &v)
{
	return space_matrix
	       (v.x(),  su(0), su(0), su(0),
	        su(0), v.y(),  su(0), su(0),
	        su(0),  su(0), v.z(), su(0),
	        su(0),  su(0), su(0), su(1));
}

sge::math::space_matrix const
sge::math::matrix_scaling(
	space_unit const x,
	space_unit const y,
	space_unit const z)
{
	return matrix_scaling(
		basic_vector<space_unit, 3>(
			x,
			y,
			z));
}

#undef near
#undef far

sge::math::space_matrix const
sge::math::matrix_perspective(
	space_unit const aspect,
	space_unit const fov,
	space_unit const near,
	space_unit const far)
{
	if(compare(far, near))
		throw exception(
			SGE_TEXT("matrix_perspective(): far may not be near!"));
	if(almost_zero(near))
		throw exception(
			SGE_TEXT("matrix_perspective(): near must not be 0!"));

	space_unit const
		h = static_cast<space_unit>(1) / std::tan(fov / static_cast<space_unit>(2)),
		w = h / aspect,
		q = (far + near) / (far - near);
	return space_matrix
	       (    w, su(0),                     su(0), su(0),
	        su(0),     h,                     su(0), su(0),
	        su(0), su(0),                         q, su(1),
	        su(0), su(0), su(2)*far*near/(near-far), su(0));
}

sge::math::space_matrix const
sge::math::matrix_orthogonal_xy()
{
	return space_matrix
	       (su(1), su(0), su(0), su(0),
	        su(0), su(1), su(0), su(0),
	        su(0), su(0), su(0), su(0),
	        su(0), su(0), su(0), su(1));
}

sge::math::space_matrix const
sge::math::matrix_rotation_z(
	space_unit const angle)
{
	space_unit const
		sinx = std::sin(angle),
		cosx = std::cos(angle);
	return space_matrix
	       (cosx,  -sinx, su(0), su(0),
	        sinx,   cosx, su(0), su(0),
	        su(0), su(0), su(1), su(0),
	        su(0), su(0), su(0), su(1));
}

sge::math::space_matrix const sge::math::matrix_rotation_y(
	space_unit const angle)
{
	space_unit const
		sinx = std::sin(angle),
		cosx = std::cos(angle);
	return space_matrix
	       ( cosx, su(0), -sinx, su(0),
	        su(0), su(1), su(0), su(0),
	         sinx, su(0),  cosx, su(0),
	        su(0), su(0), su(0), su(1));
}

sge::math::space_matrix const
sge::math::matrix_rotation_x(
	space_unit const angle)
{
	space_unit const
		sinx = std::sin(angle),
		cosx = std::cos(angle);
	return space_matrix
	       (su(1), su(0), su(0), su(0),
	        su(0),  cosx, -sinx, su(0),
	        su(0),  sinx,  cosx, su(0),
	        su(0), su(0), su(0), su(1));
}

sge::math::basic_matrix<sge::space_unit, 2, 2> const
sge::math::matrix_rotation_2d(
	space_unit const angle)
{
	space_unit const
		sinx = std::sin(angle),
        	cosx = std::cos(angle);

	return basic_matrix<space_unit, 2, 2>(
		cosx, -sinx,
		sinx,  cosx);
}

sge::math::space_matrix const
sge::math::matrix_identity()
{
	return space_matrix
	       (su(1), su(0), su(0), su(0),
	        su(0), su(1), su(0), su(0),
	        su(0), su(0), su(1), su(0),
	        su(0), su(0), su(0), su(1));
}

sge::math::space_matrix const
sge::math::matrix_orthogonal_xy(
	space_unit const left,
	space_unit const right,
	space_unit const top,
	space_unit const bottom,
	space_unit const near,
	space_unit const far)
{
	return space_matrix
	       (su(2)/(right - left),                su(0),               su(0), -(right+left)/(right-left),
	                       su(0), su(2)/(top - bottom),               su(0), -(top+bottom)/(top-bottom),
	                       su(0),                su(0), su(-2)/(far - near), -(far+near)/(far-near),
	                       su(0),                su(0),               su(0), su(1));
}

sge::math::space_matrix const
sge::math::matrix_orthogonal_xy(
	space_unit const left,
	space_unit const right,
	space_unit const top,
	space_unit const bottom)
{
	return space_matrix
	       (su(2)/(right - left),                su(0),su(0), -(right+left)/(right-left),
	                       su(0), su(2)/(top - bottom),su(0), -(top+bottom)/(top-bottom),
	                       su(0),                su(0),su(0), su(0),
	                       su(0),                su(0),su(0), su(1));
}
