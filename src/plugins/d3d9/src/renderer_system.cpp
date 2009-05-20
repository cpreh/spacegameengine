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



#include "../renderer_system.hpp"
#include "../conversion.hpp"
#include "../renderer.hpp"
#include "../constants.hpp"
#include "../enumeration.hpp"
#include <sge/exception.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/windows/create_window.hpp>

sge::d3d9::renderer_system::renderer_system()
:
	sys(
		Direct3DCreate9(
			D3D_SDK_VERSION
		)
	)
{
	if(!sys)
		throw exception(
			SGE_TEXT("Initialization of d3d failed!")
		);
}

sge::renderer::device_ptr const
sge::d3d9::system::create_renderer(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	window::instance_ptr const wnd)
{
	//const win32_window_ptr wnd(wnd_param ? dynamic_pointer_cast<win32_window>(wnd_param) : win32_window_ptr(new win32_window(param.mode.size)));
	windows::window_ptr const win32_wnd(
		dynamic_pointer_cast<
			windows::window
		>(wnd_param)
	);

	DWORD const tnl_flags(
		get_tnl_caps(
			adapter,
			sys
		)
	);

	D3DPRESENT_PARAMETERS const pp(
		create_present_parameters(
			param,
			adapter,
			wnd,
			sys
		)
	);

	ShowCursor(FALSE);

	IDirect3DDevice9* device;

	if(sys->CreateDevice(adapter, D3DDEVTYPE_HAL, wnd->hwnd(), tnl_flags, &pp, &device) != D3D_OK)
		throw exception(SGE_TEXT("Failed to initialize the renderer"));

	d3d_device_ptr const device_p(device); // FIXME this can leak memory!

	return make_shared_ptr<
		device
	>(
		device_p,
		param,
		pp,
		wnd
	);
}

sge::window::instance_ptr const
sge::d3d9::system::create_window(
	window::parameters const &wparam,
	renderer::parameters const &rparam)
{
	return sge::windows::create_window(
		wparam,
		rparam
	);
}
