//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/devicefuncs/reset.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


bool
sge::d3d9::devicefuncs::reset(
	IDirect3DDevice9 &_device,
	D3DPRESENT_PARAMETERS &_present_parameters
)
{
	switch(
		_device.Reset(
			&_present_parameters
		)
	)
	{
	case D3D_OK:
		return true;
	case D3DERR_DEVICELOST:
		return false;
	case D3DERR_DRIVERINTERNALERROR:
		throw sge::renderer::exception(
			FCPPT_TEXT("D3D internal driver error on reset!")
		);
	case D3DERR_INVALIDCALL:
		throw sge::renderer::exception(
			FCPPT_TEXT("D3D invalid call on reset!")
		);
	default:
		throw sge::renderer::exception(
			FCPPT_TEXT("d3d reset failed!")
		);
	}
}
