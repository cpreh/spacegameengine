/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../light.hpp"
#include "../to_color_value.hpp"
#include "../vector3.hpp"
#include "../../d3dinclude.hpp"
#include <sge/renderer/light.hpp>

D3DLIGHT9 const
sge::d3d9::convert::light(
	sge::renderer::light const &_light
)
{
	D3DLIGHT9 const ret =
	{
		D3DLIGHT_SPOT, // TODO: is this ok?
		d3d9::convert::to_color_value(
			_light.diffuse()
		),
		d3d9::convert::to_color_value(
			_light.specular()
		),
		d3d9::convert::to_color_value(
			_light.ambient()
		),
		d3d9::convert::vector3(
			_light.position()
		),
		d3d9::convert::vector3(
			_light.direction()
		),
		0 // FIXME: range
		// FIXME!
	};

	return ret;
}
