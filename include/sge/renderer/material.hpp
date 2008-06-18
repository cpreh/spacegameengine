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


#ifndef SGE_RENDERER_MATERIAL_HPP_INCLUDED
#define SGE_RENDERER_MATERIAL_HPP_INCLUDED

#include "../export.hpp"
#include "../su.hpp"
#include "color.hpp"

namespace sge
{
namespace renderer
{
	
struct material {
	// FIXME: should be color_f32
	SGE_SYMBOL material(
		const color diffuse,
		const color ambient,
		const color specular,
		const color emissive,
		const space_unit power);
	
	color     diffuse,
	          ambient,
	          specular,
	          emissive;
	space_unit power;
};

}
}

#endif
