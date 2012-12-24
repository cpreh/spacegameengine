/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/state/core/depth_stencil/stencil/combined.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/combined_simple.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/depth_fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/desc.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/fail_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/func.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/pass_op.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/read_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/read_mask_all.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/value.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask_all.hpp>


sge::renderer::state::core::depth_stencil::stencil::combined_simple::combined_simple(
	sge::renderer::state::core::depth_stencil::stencil::func const _func
)
:
	func_(
		_func
	),
	ref_(
		0u
	),
	read_mask_(
		sge::renderer::state::core::depth_stencil::stencil::read_mask_all()
	),
	write_mask_(
		sge::renderer::state::core::depth_stencil::stencil::write_mask_all()
	),
	fail_op_(
		sge::renderer::state::core::depth_stencil::stencil::op::keep
	),
	depth_fail_op_(
		sge::renderer::state::core::depth_stencil::stencil::op::keep
	),
	pass_op_(
		sge::renderer::state::core::depth_stencil::stencil::op::keep
	)
{
}

sge::renderer::state::core::depth_stencil::stencil::enabled const
sge::renderer::state::core::depth_stencil::stencil::combined_simple::to_enabled() const
{
	return
		sge::renderer::state::core::depth_stencil::stencil::enabled(
			sge::renderer::state::core::depth_stencil::stencil::combined(
				sge::renderer::state::core::depth_stencil::stencil::desc(
					fail_op_,
					depth_fail_op_,
					pass_op_,
					func_
				)
			),
			ref_,
			read_mask_,
			write_mask_
		);
}

sge::renderer::state::core::depth_stencil::stencil::combined_simple &
sge::renderer::state::core::depth_stencil::stencil::combined_simple::ref(
	sge::renderer::state::core::depth_stencil::stencil::value const _value
)
{
	ref_ =
		sge::renderer::state::core::depth_stencil::stencil::ref(
			_value
		);

	return *this;
}

sge::renderer::state::core::depth_stencil::stencil::combined_simple &
sge::renderer::state::core::depth_stencil::stencil::combined_simple::read_mask(
	sge::renderer::state::core::depth_stencil::stencil::value const _value
)
{
	read_mask_ =
		sge::renderer::state::core::depth_stencil::stencil::read_mask(
			_value
		);

	return *this;
}

sge::renderer::state::core::depth_stencil::stencil::combined_simple &
sge::renderer::state::core::depth_stencil::stencil::combined_simple::write_mask(
	sge::renderer::state::core::depth_stencil::stencil::value const _value
)
{
	write_mask_ =
		sge::renderer::state::core::depth_stencil::stencil::write_mask(
			_value
		);

	return *this;
}

sge::renderer::state::core::depth_stencil::stencil::combined_simple &
sge::renderer::state::core::depth_stencil::stencil::combined_simple::fail_op(
	sge::renderer::state::core::depth_stencil::stencil::op const _op
)
{
	fail_op_ =
		sge::renderer::state::core::depth_stencil::stencil::fail_op(
			_op
		);

	return *this;
}

sge::renderer::state::core::depth_stencil::stencil::combined_simple &
sge::renderer::state::core::depth_stencil::stencil::combined_simple::depth_fail_op(
	sge::renderer::state::core::depth_stencil::stencil::op const _op
)
{
	depth_fail_op_ =
		sge::renderer::state::core::depth_stencil::stencil::depth_fail_op(
			_op
		);

	return *this;
}

sge::renderer::state::core::depth_stencil::stencil::combined_simple &
sge::renderer::state::core::depth_stencil::stencil::combined_simple::pass_op(
	sge::renderer::state::core::depth_stencil::stencil::op const _op
)
{
	pass_op_ =
		sge::renderer::state::core::depth_stencil::stencil::pass_op(
			_op
		);

	return *this;
}
