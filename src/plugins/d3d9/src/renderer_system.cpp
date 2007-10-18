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


#include "../../../exception.hpp"
#include "../../../renderer/types.hpp"
#include "../renderer_system.hpp"
#include "../conversion.hpp"
#include "../renderer.hpp"
#include "../constants.hpp"
#include "../enumeration.hpp"

sge::d3d::renderer_system::renderer_system()
 : sys(Direct3DCreate9(D3D_SDK_VERSION))
{
	if(!sys)
		throw exception("Initialization of d3d failed");
}

const sge::renderer_caps_array sge::d3d::renderer_system::caps() const
{
	sge::renderer_caps_array v;
	const UINT adapter_count = sys->GetAdapterCount();
	for(UINT ad = 0; ad < adapter_count; ++ad)
	{
		renderer_caps c;
		create_renderer_caps(ad,sys,c);
		v.push_back(c);
	}
	return v;
}

sge::renderer_ptr sge::d3d::renderer_system::create_renderer(const renderer_parameters& param, const int adapter, const window_ptr wnd_param)
{
	const win32_window_ptr wnd(wnd_param ? dynamic_pointer_cast<win32_window>(wnd_param) : win32_window_ptr(new win32_window(param.mode.size)));
	const DWORD tnl_flags = get_tnl_caps(adapter,sys);
	D3DPRESENT_PARAMETERS pp = create_present_parameters(param,adapter,wnd,sys);

	ShowCursor(FALSE);

	IDirect3DDevice9* device;
	if(sys->CreateDevice(adapter,D3DDEVTYPE_HAL,wnd->hwnd(),tnl_flags,&pp,&device) != D3D_OK)
		throw exception("Failed to initialize the renderer");

	const d3d_device_ptr device_p(device);
	return renderer_ptr(new renderer(device_p,param,adapter,wnd,sys));
}
