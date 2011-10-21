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
#include "../d3dinclude.hpp"
#include "../parameters/tnl_caps.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


sge::d3d9::d3d_device_unique_ptr
sge::d3d9::create_device(
	IDirect3D9 *const _system,
	renderer::adapter const _adapter,
	D3DPRESENT_PARAMETERS &_parameters
)
{
	IDirect3DDevice9 *ret;

	if(
		_system->CreateDevice(
			_adapter.get(),
			D3DDEVTYPE_REF,
			_parameters.hDeviceWindow,
			d3d9::parameters::tnl_caps(
				_system,
				_adapter
			),
			&_parameters,
			&ret
		)
		!= D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Failed to initialize the d3d9 renderer!")
		);

	return
		d3d9::d3d_device_unique_ptr(
			ret
		);
}
