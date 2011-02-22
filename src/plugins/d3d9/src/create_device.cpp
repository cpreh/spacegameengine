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


#include "../create_device.hpp"
#include "../create_present_parameters.hpp"
#include "../d3dinclude.hpp"
#include "../tnl_caps.hpp"
#include <sge/renderer/exception.hpp>
#include <awl/backends/windows/window/instance.hpp>
#include <awl/backends/windows/window/instance_ptr.hpp>
#include <fcppt/dynamic_pointer_cast.hpp>
#include <fcppt/text.hpp>

sge::d3d9::d3d_device_ptr const
sge::d3d9::create_device(
	d3d9::d3d_system_ptr const _system
	renderer::parameters const &_parameters,
	renderer::adapter const _adapter,
	sge::window::instance_ptr const _window
)
{
	awl::backends::windows::window::instance_ptr const windows_window(
		fcppt::dynamic_pointer_cast<
			awl::backends::windows::window::instance
		>(
			_window->awl_instance()
		)
	);

	D3DPRESENT_PARAMETERS const present_parameters(
		d3d9::create_present_parameters(
			_system,
			_parameters,
			_adapter,
			windows_window
		)
	);

	IDirect3DDevice9 *ret;

	if(
		_system->CreateDevice(
			_adapter.get(),
			D3DDEVTYPE_HAL,
			windows_window->hwnd(),
			d3d9::tnl_caps(
				_system,
				_adapter
			),
			&present_parameters,
			&device
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Failed to initialize the d3d9 renderer!")
		);

	return
		d3d9::d3d_device_ptr(
			ret
		);
}
