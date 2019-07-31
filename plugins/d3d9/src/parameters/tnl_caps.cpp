//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device_index.hpp>
#include <sge/d3d9/parameters/tnl_caps.hpp>
#include <sge/d3d9/systemfuncs/get_caps.hpp>


DWORD
sge::d3d9::parameters::tnl_caps(
	IDirect3D9 &_system,
	sge::d3d9::device_index const _index
)
{
	D3DCAPS9 const caps(
		sge::d3d9::systemfuncs::get_caps(
			_system,
			_index
		)
	);

	DWORD ret(
		0
	);

	if(
		caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT
	)
	{
		ret |= D3DCREATE_HARDWARE_VERTEXPROCESSING;

		if(
			caps.DevCaps & D3DDEVCAPS_PUREDEVICE
		)
			ret |= D3DCREATE_PUREDEVICE;
	}
	else
		ret |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	return ret;
}
