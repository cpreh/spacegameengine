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


#include "../present.hpp"
#include "../../d3dinclude.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


bool
sge::d3d9::devicefuncs::present(
	IDirect3DDevice9 *const _device
)
{
	switch(
		_device->Present(
			0,
			0,
			0,
			0
		)
	)
	{
	case D3D_OK:
		return true;
	case D3DERR_DEVICELOST:
		return false;
	default:
		throw sge::renderer::exception(
			FCPPT_TEXT("Present() failed!")
		);
	}
}
