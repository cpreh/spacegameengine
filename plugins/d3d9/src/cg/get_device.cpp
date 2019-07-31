//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/check_state.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/cg/get_device.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgD3D9.h>
#include <fcppt/config/external_end.hpp>


IDirect3DDevice9 *
sge::d3d9::cg::get_device()
{
	IDirect3DDevice9 *const ret(
		::cgD3D9GetDevice()
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgD3D9GetDevice failed"),
		sge::renderer::exception
	)

	return ret;
}
