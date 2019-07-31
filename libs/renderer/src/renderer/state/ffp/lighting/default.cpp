//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/lighting/default.hpp>
#include <sge/renderer/state/ffp/lighting/off.hpp>
#include <sge/renderer/state/ffp/lighting/parameters.hpp>
#include <sge/renderer/state/ffp/lighting/variant.hpp>


sge::renderer::state::ffp::lighting::parameters
sge::renderer::state::ffp::lighting::default_()
{
	return
		sge::renderer::state::ffp::lighting::parameters(
			sge::renderer::state::ffp::lighting::variant{
				sge::renderer::state::ffp::lighting::off()
			}
		);
}
