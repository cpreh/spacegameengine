//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/depth_stencil/stencil/combined.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/desc.hpp>


sge::renderer::state::core::depth_stencil::stencil::combined::combined(
	sge::renderer::state::core::depth_stencil::stencil::desc const &_desc
)
:
	desc_(
		_desc
	)
{
}

sge::renderer::state::core::depth_stencil::stencil::desc const &
sge::renderer::state::core::depth_stencil::stencil::combined::desc() const
{
	return
		desc_;
}
