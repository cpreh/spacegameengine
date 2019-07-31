//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/depth_stencil/stencil/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled_variant.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/read_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask.hpp>


sge::renderer::state::core::depth_stencil::stencil::enabled::enabled(
	sge::renderer::state::core::depth_stencil::stencil::enabled_variant const &_enabled_variant,
	sge::renderer::state::core::depth_stencil::stencil::ref const _ref,
	sge::renderer::state::core::depth_stencil::stencil::read_mask const _read_mask,
	sge::renderer::state::core::depth_stencil::stencil::write_mask const _write_mask
)
:
	enabled_variant_(
		_enabled_variant
	),
	ref_(
		_ref
	),
	read_mask_(
		_read_mask
	),
	write_mask_(
		_write_mask
	)
{
}

sge::renderer::state::core::depth_stencil::stencil::enabled_variant const &
sge::renderer::state::core::depth_stencil::stencil::enabled::enabled_variant() const
{
	return
		enabled_variant_;
}

sge::renderer::state::core::depth_stencil::stencil::ref
sge::renderer::state::core::depth_stencil::stencil::enabled::ref() const
{
	return
		ref_;
}

sge::renderer::state::core::depth_stencil::stencil::read_mask
sge::renderer::state::core::depth_stencil::stencil::enabled::read_mask() const
{
	return
		read_mask_;
}

sge::renderer::state::core::depth_stencil::stencil::write_mask
sge::renderer::state::core::depth_stencil::stencil::enabled::write_mask() const
{
	return
		write_mask_;
}
