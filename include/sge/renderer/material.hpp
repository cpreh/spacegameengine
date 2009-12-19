/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/image/color/any/object.hpp>
#include <sge/renderer/any_arithmetic.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace renderer
{

class material {
public:
	SGE_SYMBOL material(
		image::color::any::object const &diffuse,
		image::color::any::object const &ambient,
		image::color::any::object const &specular,
		image::color::any::object const &emissive,
		any_arithmetic const &power);

	SGE_SYMBOL image::color::any::object const &diffuse() const;
	SGE_SYMBOL image::color::any::object const &ambient() const;
	SGE_SYMBOL image::color::any::object const &specular() const;
	SGE_SYMBOL image::color::any::object const &emissive() const;
	SGE_SYMBOL any_arithmetic const &power() const;
private:
	image::color::any::object
		diffuse_,
		ambient_,
		specular_,
		emissive_;
	any_arithmetic power_;
};

}
}

#endif
