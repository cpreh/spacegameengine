//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_RASTERIZER_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_RASTERIZER_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <sge/renderer/state/core/rasterizer/enable_scissor_test.hpp>
#include <sge/renderer/state/core/rasterizer/fill_mode.hpp>
#include <sge/renderer/state/core/rasterizer/parameters_fwd.hpp>


namespace sge::renderer::state::core::rasterizer
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::state::core::rasterizer::cull_mode,
		sge::renderer::state::core::rasterizer::fill_mode,
		sge::renderer::state::core::rasterizer::enable_scissor_test
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::rasterizer::cull_mode
	cull_mode() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::rasterizer::fill_mode
	fill_mode() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::rasterizer::enable_scissor_test
	enable_scissor_test() const;
private:
	sge::renderer::state::core::rasterizer::cull_mode cull_mode_;

	sge::renderer::state::core::rasterizer::fill_mode fill_mode_;

	sge::renderer::state::core::rasterizer::enable_scissor_test enable_scissor_test_;
};

}

#endif
