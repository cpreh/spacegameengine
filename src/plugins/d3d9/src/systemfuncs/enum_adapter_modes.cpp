/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/d3d9/optional_display_mode.hpp>
#include <sge/d3d9/systemfuncs/enum_adapter_modes.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/device/index.hpp>
#include <fcppt/text.hpp>


sge::d3d9::optional_display_mode
sge::d3d9::systemfuncs::enum_adapter_modes(
	IDirect3D9 &_d3d9,
	sge::renderer::device::index const _adapter,
	D3DFORMAT const _format,
	UINT const _mode
)
{
	D3DDISPLAYMODE result;

	switch(
		_d3d9.EnumAdapterModes(
			_adapter.get(),
			_format,
			_mode,
			&result
		)
	)
	{
	case D3D_OK:
		return
			sge::d3d9::optional_display_mode(
				result
			);
	case D3DERR_NOTAVAILABLE:
		return
			sge::d3d9::optional_display_mode();
	default:
		throw
			sge::renderer::exception(
				FCPPT_TEXT("EnumAdapterModes failed")
			);
	}
}
