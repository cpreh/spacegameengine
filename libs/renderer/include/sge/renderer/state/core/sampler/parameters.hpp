//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/sampler/parameters_fwd.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/parameters.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace sampler
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::state::core::sampler::address::parameters const &,
		sge::renderer::state::core::sampler::filter::parameters const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::address::parameters const &
	address() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::filter::parameters const &
	filter() const;
private:
	sge::renderer::state::core::sampler::address::parameters address_;

	sge::renderer::state::core::sampler::filter::parameters filter_;
};

}
}
}
}
}

#endif
