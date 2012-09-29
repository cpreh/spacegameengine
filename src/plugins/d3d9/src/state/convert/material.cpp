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
#include <sge/d3d9/convert/to_color_value.hpp>
#include <sge/d3d9/state/convert/material.hpp>
#include <sge/renderer/state/ffp/lighting/material/parameters.hpp>


D3DMATERIAL9 const
sge::d3d9::state::convert::material(
	sge::renderer::state::ffp::lighting::material::parameters const &_material
)
{
	D3DMATERIAL9 const ret =
	{
		sge::d3d9::convert::to_color_value(
			_material.diffuse().get()
		),
		sge::d3d9::convert::to_color_value(
			_material.ambient().get()
		),
		sge::d3d9::convert::to_color_value(
			_material.specular().get()
		),
		sge::d3d9::convert::to_color_value(
			_material.emissive().get()
		),
		_material.shininess().get()
	};

	return ret;
}
