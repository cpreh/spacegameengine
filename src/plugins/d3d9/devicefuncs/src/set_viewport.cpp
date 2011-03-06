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


#include "../set_viewport.hpp"
#include "../../convert/viewport.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

void
sge::d3d9::devicefuncs::set_viewport(
	IDirect3DDevice9 *const _device,
	sge::renderer::viewport const &_viewport
)
{
	D3DVIEWPORT9 const d3d_viewport(
		d3d9::convert::viewport(
			_viewport
		)
	);

	if(
		_device->SetViewport(
			&d3d_viewport
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("SetViewport() failed!")
		);
}
