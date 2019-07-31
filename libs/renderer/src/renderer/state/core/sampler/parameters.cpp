//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/parameters.hpp>


sge::renderer::state::core::sampler::parameters::parameters(
	sge::renderer::state::core::sampler::address::parameters const &_address,
	sge::renderer::state::core::sampler::filter::parameters const &_filter
)
:
	address_(
		_address
	),
	filter_(
		_filter
	)
{
}

sge::renderer::state::core::sampler::address::parameters const &
sge::renderer::state::core::sampler::parameters::address() const
{
	return address_;
}

sge::renderer::state::core::sampler::filter::parameters const &
sge::renderer::state::core::sampler::parameters::filter() const
{
	return filter_;
}
