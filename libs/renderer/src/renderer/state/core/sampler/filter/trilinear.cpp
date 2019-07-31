//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/sampler/filter/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/trilinear.hpp>
#include <sge/renderer/state/core/sampler/filter/variant.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mag.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/min.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/mip.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters.hpp>


sge::renderer::state::core::sampler::filter::parameters
sge::renderer::state::core::sampler::filter::trilinear()
{
	return
		sge::renderer::state::core::sampler::filter::parameters(
			sge::renderer::state::core::sampler::filter::variant{
				sge::renderer::state::core::sampler::filter::normal::parameters(
					sge::renderer::state::core::sampler::filter::normal::mag::linear,
					sge::renderer::state::core::sampler::filter::normal::min::linear,
					sge::renderer::state::core::sampler::filter::normal::mip::linear
				)
			}
		);
}
