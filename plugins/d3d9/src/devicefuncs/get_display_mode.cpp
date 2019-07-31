//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/get_display_mode.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


D3DDISPLAYMODE const
sge::d3d9::devicefuncs::get_display_mode(
	IDirect3DDevice9 &_device,
	UINT const _swap_chain
)
{
	D3DDISPLAYMODE ret;

	if(
		_device.GetDisplayMode(
			_swap_chain,
			&ret
		)
		!=
		D3D_OK
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("GetDisplayMode failed!")
		);

	return
		ret;
}
