/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../../../ptr_cast.hpp"
#include "../../../util.hpp"
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
		throw std::runtime_error("Initialization of d3d failed");
}

void sge::d3d::renderer_system::caps(renderer_caps_array& v) const
{
	const unsigned adapter_count = sys->GetAdapterCount();
	for(unsigned ad = 0; ad < adapter_count; ++ad)
	{
		renderer_caps c;
		create_renderer_caps(ad,sys,c);
		v.push_back(c);
	}
}

sge::renderer_ptr sge::d3d::renderer_system::create_renderer(const renderer_parameters& param, const int adapter, const window_ptr wnd_param)
{
	const win32_window_ptr wnd(wnd_param ? dynamic_pointer_cast<win32_window>(wnd_param) : win32_window_ptr(new win32_window(param.mode.size, !param.windowed)));
	const DWORD tnl_flags = get_tnl_caps(adapter,sys);
	D3DPRESENT_PARAMETERS pp = create_present_parameters(param,adapter,wnd,sys);

	ShowCursor(FALSE);

	IDirect3DDevice9* device;
	if(sys->CreateDevice(adapter,D3DDEVTYPE_HAL,wnd->hwnd(),tnl_flags,&pp,&device) != D3D_OK)
		throw std::runtime_error("Failed to initialize the renderer");

	const d3d_device_ptr device_p(device);
	return renderer_ptr(new renderer(device_p,param,adapter,wnd,sys));
}
