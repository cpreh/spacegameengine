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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/convert/light/cutoff_angle.hpp>
#include <sge/d3d9/convert/light/direction.hpp>
#include <sge/d3d9/convert/light/directional.hpp>
#include <sge/renderer/light/directional.hpp>


void
sge::d3d9::convert::light::directional(
	D3DLIGHT9 &_light,
	renderer::light::directional const &_directional
)
{
	_light.Type = D3DLIGHT_DIRECTIONAL;

	light::direction(
		_light,
		_directional.direction()
	);

	light::cutoff_angle(
		_light,
		_directional.cutoff_angle()
	);
}
