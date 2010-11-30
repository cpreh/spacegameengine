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
	image::color::any::object const &_ambient,
	image::color::any::object const &_diffuse,
	image::color::any::object const &_specular,
	position_type const &_position,
	direction_type const &_direction,
	attenuation_type const &_const_attenuation,
	attenuation_type const &_linear_attenuation,
	attenuation_type const &_quadratic_attenuation,
	scalar const &_distribution_exponent,
	scalar const &_cutoff_angle
)
:
	ambient_(_ambient),
	diffuse_(_diffuse),
	specular_(_specular),
	position_(_position),
	direction_(_direction),
	const_attenuation_(_const_attenuation),
	linear_attenuation_(_linear_attenuation),
	quadratic_attenuation_(_quadratic_attenuation),
	distribution_exponent_(_distribution_exponent),
	cutoff_angle_(_cutoff_angle)
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

sge::renderer::scalar const &
sge::renderer::light::distribution_exponent() const
{
	return distribution_exponent_;
}

sge::renderer::scalar const &
sge::renderer::light::cutoff_angle() const
{
	return cutoff_angle_;
}
