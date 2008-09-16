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
#include "../math/vector.hpp"
#include "../export.hpp"

namespace sge
{
namespace renderer
{

struct light {
public:
	typedef math::vector3 position_type;
	typedef math::vector3 direction_type;
	typedef space_unit attenuation_type;

	SGE_SYMBOL light(
		any_color const &ambient,
		any_color const &diffuse,
		any_color const &specular,
		position_type const &pos,
		direction_type const &dir,
		attenuation_type const_attenuation,
		attenuation_type linear_attenuation,
		attenuation_type quadratic_attenuation,
		space_unit       distribution_exponent,
		space_unit       cutoff_angle);

	any_color        ambient,
	                 diffuse,
	                 specular;
	position_type    pos;
	direction_type   dir;
	attenuation_type const_attenuation,
	                 linear_attenuation,
	                 quadratic_attenuation;
	space_unit       distribution_exponent,
	                 cutoff_angle;
};

typedef unsigned light_index;

}
}

#endif
