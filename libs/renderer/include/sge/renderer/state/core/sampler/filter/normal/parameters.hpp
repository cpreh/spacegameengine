//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_NORMAL_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_SAMPLER_FILTER_NORMAL_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mag.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/min.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters_fwd.hpp>


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
namespace normal
{

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::state::core::sampler::filter::normal::mag,
		sge::renderer::state::core::sampler::filter::normal::min,
		sge::renderer::state::core::sampler::filter::normal::mip
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::filter::normal::mag
	mag() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::filter::normal::min
	min() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::sampler::filter::normal::mip
	mip() const;
private:
	sge::renderer::state::core::sampler::filter::normal::mag mag_;

	sge::renderer::state::core::sampler::filter::normal::min min_;

	sge::renderer::state::core::sampler::filter::normal::mip mip_;
};

SGE_RENDERER_DETAIL_SYMBOL
bool
operator==(
	sge::renderer::state::core::sampler::filter::normal::parameters const &,
	sge::renderer::state::core::sampler::filter::normal::parameters const &
);

}
}
}
}
}
}
}

#endif
