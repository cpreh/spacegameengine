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


#include <sge/renderer/light.hpp>

sge::renderer::light::light(
	any_color const &ambient,
	any_color const &diffuse,
	any_color const &specular,
	position_type const &pos,
	direction_type const &dir,
	attenuation_type const const_attenuation,
	attenuation_type const linear_attenuation,
	attenuation_type const quadratic_attenuation,
	space_unit const distribution_exponent,
	space_unit const cutoff_angle)
: ambient(ambient),
  diffuse(diffuse),
  specular(specular),
  pos(pos),
  dir(dir),
  const_attenuation(const_attenuation),
  linear_attenuation(linear_attenuation),
  quadratic_attenuation(quadratic_attenuation),
  distribution_exponent(distribution_exponent),
  cutoff_angle(cutoff_angle)
{}
