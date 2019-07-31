//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device_index.hpp>
#include <sge/d3d9/optional_display_mode.hpp>
#include <sge/d3d9/systemfuncs/enum_adapter_modes.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


sge::d3d9::optional_display_mode
sge::d3d9::systemfuncs::enum_adapter_modes(
	IDirect3D9 &_d3d9,
	sge::d3d9::device_index const _adapter,
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
