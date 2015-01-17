/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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

sge::renderer::state::core::depth_stencil::stencil::fail_op const
sge::renderer::state::core::depth_stencil::stencil::desc::fail_op() const
{
	return fail_op_;
}

sge::renderer::state::core::depth_stencil::stencil::depth_fail_op const
sge::renderer::state::core::depth_stencil::stencil::desc::depth_fail_op() const
{
	return depth_fail_op_;
}

sge::renderer::state::core::depth_stencil::stencil::pass_op const
sge::renderer::state::core::depth_stencil::stencil::desc::pass_op() const
{
	return pass_op_;
}

sge::renderer::state::core::depth_stencil::stencil::func
sge::renderer::state::core::depth_stencil::stencil::desc::func() const
{
	return func_;
}
