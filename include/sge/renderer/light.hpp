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


#ifndef SGE_RENDERER_LIGHT_HPP_INCLUDED
#define SGE_RENDERER_LIGHT_HPP_INCLUDED

#include "any_color.hpp"
#include "any_vector3.hpp"
#include "any_arithmetic.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace renderer
{

struct light {
	typedef any_vector3 position_type;
	typedef any_vector3 direction_type;
	typedef any_arithmetic attenuation_type;

	SGE_SYMBOL light(
		any_color const &ambient,
		any_color const &diffuse,
		any_color const &specular,
		position_type const &pos,
		direction_type const &dir,
		attenuation_type const &const_attenuation,
		attenuation_type const &linear_attenuation,
		attenuation_type const &quadratic_attenuation,
		any_arithmetic const &distribution_exponent,
		any_arithmetic const &cutoff_angle);
	
	SGE_SYMBOL any_color const &ambient() const;
	SGE_SYMBOL any_color const &diffuse() const;
	SGE_SYMBOL any_color const &specular() const;
	SGE_SYMBOL position_type const &position() const;
	SGE_SYMBOL direction_type const &direction() const;
	SGE_SYMBOL attenuation_type const &const_attenuation() const;
	SGE_SYMBOL attenuation_type const &linear_attenuation() const;
	SGE_SYMBOL attenuation_type const &quadratic_attenuation() const;
	SGE_SYMBOL any_arithmetic const &distribution_exponent() const;
	SGE_SYMBOL any_arithmetic const &cutoff_angle() const;
private:
	any_color        ambient_,
	                 diffuse_,
	                 specular_;
	position_type    position_;
	direction_type   direction_;
	attenuation_type const_attenuation_,
	                 linear_attenuation_,
	                 quadratic_attenuation_;
	any_arithmetic   distribution_exponent_,
	                 cutoff_angle_;
};

}
}

#endif
