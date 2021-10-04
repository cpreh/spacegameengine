//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_ADDRESS_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_ADDRESS_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/sampler/address/mode_s.hpp>
#include <sge/renderer/state/core/sampler/address/mode_t.hpp>
#include <sge/renderer/state/core/sampler/address/mode_u.hpp>
#include <sge/renderer/state/core/sampler/address/parameters_fwd.hpp>


namespace sge::renderer::state::core::sampler::address
{

class parameters
{
public:
	parameters(
		sge::renderer::state::core::sampler::address::mode_s,
		sge::renderer::state::core::sampler::address::mode_t,
		sge::renderer::state::core::sampler::address::mode_u
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::address::mode_s
	mode_s() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::address::mode_t
	mode_t() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::address::mode_u
	mode_u() const;
private:
	sge::renderer::state::core::sampler::address::mode_s mode_s_;

	sge::renderer::state::core::sampler::address::mode_t mode_t_;

	sge::renderer::state::core::sampler::address::mode_u mode_u_;
};

SGE_RENDERER_DETAIL_SYMBOL
bool
operator==(
	sge::renderer::state::core::sampler::address::parameters const &,
	sge::renderer::state::core::sampler::address::parameters const &
);

}

#endif
