//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <sge/renderer/state/core/rasterizer/enable_scissor_test.hpp>
#include <sge/renderer/state/core/rasterizer/fill_mode.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>


sge::renderer::state::core::rasterizer::parameters::parameters(
	sge::renderer::state::core::rasterizer::cull_mode const _cull_mode,
	sge::renderer::state::core::rasterizer::fill_mode const _fill_mode,
	sge::renderer::state::core::rasterizer::enable_scissor_test const _enable_scissor_test
)
:
	cull_mode_(
		_cull_mode
	),
	fill_mode_(
		_fill_mode
	),
	enable_scissor_test_(
		_enable_scissor_test
	)
{
}

sge::renderer::state::core::rasterizer::cull_mode
sge::renderer::state::core::rasterizer::parameters::cull_mode() const
{
	return
		cull_mode_;
}

sge::renderer::state::core::rasterizer::fill_mode
sge::renderer::state::core::rasterizer::parameters::fill_mode() const
{
	return
		fill_mode_;
}

sge::renderer::state::core::rasterizer::enable_scissor_test
sge::renderer::state::core::rasterizer::parameters::enable_scissor_test() const
{
	return
		enable_scissor_test_;
}
