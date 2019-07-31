//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/alpha_test/default.hpp>
#include <sge/renderer/state/ffp/alpha_test/off.hpp>
#include <sge/renderer/state/ffp/alpha_test/parameters.hpp>
#include <sge/renderer/state/ffp/alpha_test/variant.hpp>


sge::renderer::state::ffp::alpha_test::parameters
sge::renderer::state::ffp::alpha_test::default_()
{
	return
		sge::renderer::state::ffp::alpha_test::parameters(
			sge::renderer::state::ffp::alpha_test::variant{
				sge::renderer::state::ffp::alpha_test::off()
			}
		);
}
