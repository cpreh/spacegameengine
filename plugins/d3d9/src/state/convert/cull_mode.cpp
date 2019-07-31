//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/cull_mode.hpp>
#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DCULL
sge::d3d9::state::convert::cull_mode(
	sge::renderer::state::core::rasterizer::cull_mode const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::state::core::rasterizer::cull_mode::off:
		return D3DCULL_NONE;
	case sge::renderer::state::core::rasterizer::cull_mode::clockwise:
		return D3DCULL_CW;
	case sge::renderer::state::core::rasterizer::cull_mode::counter_clockwise:
		return D3DCULL_CCW;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
