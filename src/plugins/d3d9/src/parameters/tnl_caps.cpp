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
#include <sge/d3d9/parameters/tnl_caps.hpp>
#include <sge/d3d9/systemfuncs/get_caps.hpp>


DWORD
sge::d3d9::parameters::tnl_caps(
	IDirect3D9 *const _system,
	renderer::adapter const _adapter
)
{
	D3DCAPS9 const caps(
		systemfuncs::get_caps(
			_system,
			_adapter
		)
	);

	DWORD ret(
		0
	);

	if(
		caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT
	)
	{
		ret |= D3DCREATE_HARDWARE_VERTEXPROCESSING;

		if(
			caps.DevCaps & D3DDEVCAPS_PUREDEVICE
		)
			ret |= D3DCREATE_PUREDEVICE;
	}
	else
		ret |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	return ret;
}
