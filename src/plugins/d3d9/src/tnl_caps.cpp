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


#include "../tnl_caps.hpp"

DWORD
sge::d3d9::tnl_caps(
	renderer::adapter_type const adapter,
	d3d_ptr const sys)
{
	DWORD r = 0;

	D3DCAPS9 caps;

	sys->GetDeviceCaps(
		adapter,
		D3DDEVTYPE_HAL,
		&caps
	);

	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		r |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
		if(caps.DevCaps & D3DDEVCAPS_PUREDEVICE)
			r |= D3DCREATE_PUREDEVICE;
	}
	else
		r |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	return r;
}
