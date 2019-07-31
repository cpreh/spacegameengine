//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/swapchainfuncs/present.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <fcppt/text.hpp>


bool
sge::d3d9::swapchainfuncs::present(
	IDirect3DSwapChain9 &_swap_chain,
	sge::renderer::pixel_format::srgb const _srgb
)
{
	// TODO: Does this silently fail to do gamma correction if srgb is not supported?
	switch(
		_swap_chain.Present(
			nullptr,
			nullptr,
			nullptr,
			nullptr,
			static_cast<
				DWORD
			>(
				_srgb
				==
				sge::renderer::pixel_format::srgb::no
				?
					0L
				:
					D3DPRESENT_LINEAR_CONTENT
			)
		)
	)
	{
	case D3D_OK:
		return true;
	case D3DERR_DEVICELOST:
		return false;
	default:
		throw sge::renderer::exception(
			FCPPT_TEXT("Present() failed!")
		);
	}
}
