//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/sampler/filter/parameters_fwd.hpp>
#include <sge/renderer/state/core/sampler/filter/variant.hpp>


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
namespace filter
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	parameters(
		sge::renderer::state::core::sampler::filter::variant const &
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::filter::variant const &
	variant() const;
private:
	sge::renderer::state::core::sampler::filter::variant variant_;
};

SGE_RENDERER_DETAIL_SYMBOL
bool
operator==(
	sge::renderer::state::core::sampler::filter::parameters const &,
	sge::renderer::state::core::sampler::filter::parameters const &
);

}
}
}
}
}
}

#endif
