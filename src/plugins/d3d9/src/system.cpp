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


#include "../system.hpp"
#include "../device.hpp"
#include "../create_caps.hpp"
#include "../present_parameters.hpp"
#include "../tnl_caps.hpp"
#include <sge/exception.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/windows/create_window.hpp>
#include <sge/make_shared_ptr.hpp>

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
			FCPPT_TEXT("Initialization of d3d failed!")
		);
}

sge::renderer::device_ptr const
sge::d3d9::system::create_renderer(
	renderer::parameters const &param,
	renderer::adapter_type const adapter,
	window::instance_ptr const wnd)
{
	windows::window_ptr const wnd(
		dynamic_pointer_cast<
			windows::window
		>(wnd_param)
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

	IDirect3DDevice9 *device;

	if(
		sys->CreateDevice(
			adapter,
			D3DDEVTYPE_HAL,
			wnd->hwnd(),
			tnl_caps(
				adapter,
				sys
			),
			&pp,
			&device
		) != D3D_OK
	)
		throw exception(
			FCPPT_TEXT("Failed to initialize the renderer")
		);

	d3d_device_ptr const device_p(
		device
	);

	return make_shared_ptr<
		device
	>(
		device_p,
		param,
		pp,
		wnd,
		create_caps(
			adapter,
			sys
		)
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
