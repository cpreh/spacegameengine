//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/depth_stencil/depth/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/func.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/write_enable.hpp>


sge::renderer::state::core::depth_stencil::depth::enabled::enabled(
	sge::renderer::state::core::depth_stencil::depth::func const _func,
	sge::renderer::state::core::depth_stencil::depth::write_enable const _write_enable
)
:
	func_(
		_func
	),
	write_enable_(
		_write_enable
	)
{
}

sge::renderer::state::core::depth_stencil::depth::func
sge::renderer::state::core::depth_stencil::depth::enabled::func() const
{
	return
		func_;
}

sge::renderer::state::core::depth_stencil::depth::write_enable
sge::renderer::state::core::depth_stencil::depth::enabled::write_enable() const
{
	return
		write_enable_;
}
