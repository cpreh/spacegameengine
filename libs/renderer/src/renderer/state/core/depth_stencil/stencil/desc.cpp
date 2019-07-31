//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/depth_stencil/stencil/depth_fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/desc.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/func.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/pass_op.hpp>


sge::renderer::state::core::depth_stencil::stencil::desc::desc(
	sge::renderer::state::core::depth_stencil::stencil::fail_op const _fail_op,
	sge::renderer::state::core::depth_stencil::stencil::depth_fail_op const _depth_fail_op,
	sge::renderer::state::core::depth_stencil::stencil::pass_op const _pass_op,
	sge::renderer::state::core::depth_stencil::stencil::func const _func
)
:
	fail_op_(
		_fail_op
	),
	depth_fail_op_(
		_depth_fail_op
	),
	pass_op_(
		_pass_op
	),
	func_(
		_func
	)
{
}

sge::renderer::state::core::depth_stencil::stencil::fail_op
sge::renderer::state::core::depth_stencil::stencil::desc::fail_op() const
{
	return
		fail_op_;
}

sge::renderer::state::core::depth_stencil::stencil::depth_fail_op
sge::renderer::state::core::depth_stencil::stencil::desc::depth_fail_op() const
{
	return
		depth_fail_op_;
}

sge::renderer::state::core::depth_stencil::stencil::pass_op
sge::renderer::state::core::depth_stencil::stencil::desc::pass_op() const
{
	return
		pass_op_;
}

sge::renderer::state::core::depth_stencil::stencil::func
sge::renderer::state::core::depth_stencil::stencil::desc::func() const
{
	return
		func_;
}
