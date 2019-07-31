//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/check_state.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/cg/scoped_device.hpp>
#include <sge/d3d9/cg/program/optimal_options.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgD3D9.h>
#include <fcppt/config/external_end.hpp>


sge::cg::program::compile_options const
sge::d3d9::cg::program::optimal_options(
	IDirect3DDevice9 &_device,
	sge::cg::profile::object const &_profile
)
{
	sge::d3d9::cg::scoped_device const context(
		_device
	);

	char const ** const ret =
		::cgD3D9GetOptimalOptions(
			_profile.get()
		);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgD3D9GetOptimalOptions failed"),
		sge::renderer::exception
	)

	FCPPT_ASSERT_ERROR(
		ret
		!=
		nullptr
	);

	return
		sge::cg::program::compile_options(
			ret
		);
}
