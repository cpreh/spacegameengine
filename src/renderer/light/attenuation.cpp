/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/light/attenuation.hpp>

sge::renderer::light::attenuation::attenuation(
	light::constant_attenuation const _constant_attenuation,
	light::linear_attenuation const _linear_attenuation,
	light::quadratic_attenuation const _quadratic_attenuation
)
:
	constant_attenuation_(_constant_attenuation),
	linear_attenuation_(_linear_attenuation),
	quadratic_attenuation_(_quadratic_attenuation)
{
}

sge::renderer::light::constant_attenuation const
sge::renderer::light::attenuation::constant_attenuation() const
{
	return constant_attenuation_;
}

sge::renderer::light::linear_attenuation const
sge::renderer::light::attenuation::linear_attenuation() const
{
	return linear_attenuation_;
}

sge::renderer::light::quadratic_attenuation const
sge::renderer::light::attenuation::quadratic_attenuation() const
{
	return quadratic_attenuation_;
}
