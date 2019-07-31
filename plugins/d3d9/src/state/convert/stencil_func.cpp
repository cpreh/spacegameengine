//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/stencil_func.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/func.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DCMPFUNC
sge::d3d9::state::convert::stencil_func(
	sge::renderer::state::core::depth_stencil::stencil::func const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::state::core::depth_stencil::stencil::func::never:
		return D3DCMP_NEVER;
	case sge::renderer::state::core::depth_stencil::stencil::func::less:
		return D3DCMP_LESS;
	case sge::renderer::state::core::depth_stencil::stencil::func::equal:
		return D3DCMP_EQUAL;
	case sge::renderer::state::core::depth_stencil::stencil::func::less_equal:
		return D3DCMP_LESSEQUAL;
	case sge::renderer::state::core::depth_stencil::stencil::func::greater:
		return D3DCMP_GREATER;
	case sge::renderer::state::core::depth_stencil::stencil::func::not_equal:
		return D3DCMP_NOTEQUAL;
	case sge::renderer::state::core::depth_stencil::stencil::func::greater_equal:
		return D3DCMP_GREATEREQUAL;
	case sge::renderer::state::core::depth_stencil::stencil::func::always:
		return D3DCMP_ALWAYS;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
