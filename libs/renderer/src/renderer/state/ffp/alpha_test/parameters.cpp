//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/alpha_test/parameters.hpp>
#include <sge/renderer/state/ffp/alpha_test/variant.hpp>


sge::renderer::state::ffp::alpha_test::parameters::parameters(
	sge::renderer::state::ffp::alpha_test::variant const &_variant
)
:
	variant_(
		_variant
	)
{
}

sge::renderer::state::ffp::alpha_test::variant const &
sge::renderer::state::ffp::alpha_test::parameters::variant() const
{
	return
		variant_;
}
