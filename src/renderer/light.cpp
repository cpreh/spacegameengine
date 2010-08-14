/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
	image::color::any::object const &ambient_,
	image::color::any::object const &diffuse_,
	image::color::any::object const &specular_,
	position_type const &position_,
	direction_type const &direction_,
	attenuation_type const &const_attenuation_,
	attenuation_type const &linear_attenuation_,
	attenuation_type const &quadratic_attenuation_,
	any_arithmetic const &distribution_exponent_,
	any_arithmetic const &cutoff_angle_)
:
	ambient_(ambient_),
	diffuse_(diffuse_),
	specular_(specular_),
	position_(position_),
	direction_(direction_),
	const_attenuation_(const_attenuation_),
	linear_attenuation_(linear_attenuation_),
	quadratic_attenuation_(quadratic_attenuation_),
	distribution_exponent_(distribution_exponent_),
	cutoff_angle_(cutoff_angle_)
{}

sge::image::color::any::object const &
sge::renderer::light::ambient() const
{
	return ambient_;
}

sge::image::color::any::object const &
sge::renderer::light::diffuse() const
{
	return diffuse_;
}

sge::image::color::any::object const &
sge::renderer::light::specular() const
{
	return specular_;
}

sge::renderer::light::position_type const &
sge::renderer::light::position() const
{
	return position_;
}

sge::renderer::light::direction_type const &
sge::renderer::light::direction() const
{
	return direction_;
}

sge::renderer::light::attenuation_type const &
sge::renderer::light::const_attenuation() const
{
	return const_attenuation_;
}

sge::renderer::light::attenuation_type const &
sge::renderer::light::linear_attenuation() const
{
	return linear_attenuation_;
}

sge::renderer::light::attenuation_type const &
sge::renderer::light::quadratic_attenuation() const
{
	return quadratic_attenuation_;
}

sge::renderer::any_arithmetic const &
sge::renderer::light::distribution_exponent() const
{
	return distribution_exponent_;
}

sge::renderer::any_arithmetic const &
sge::renderer::light::cutoff_angle() const
{
	return cutoff_angle_;
}
