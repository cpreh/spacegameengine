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
#include "any_color.hpp"
#include "any_arithmetic.hpp"

namespace sge
{
namespace renderer
{
	
struct material {
	SGE_SYMBOL material(
		any_color const &diffuse,
		any_color const &ambient,
		any_color const &specular,
		any_color const &emissive,
		any_arithmetic const &power);
	
	SGE_SYMBOL any_color const &diffuse() const;
	SGE_SYMBOL any_color const &ambient() const;
	SGE_SYMBOL any_color const &specular() const;
	SGE_SYMBOL any_color const &emissive() const;
	SGE_SYMBOL any_arithmetic const &power() const;
private:
	any_color diffuse_,
	          ambient_,
	          specular_,
	          emissive_;
	any_arithmetic power_;
};

}
}

#endif
