//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/alpha_test/enabled.hpp>
#include <sge/renderer/state/ffp/alpha_test/func.hpp>
#include <sge/renderer/state/ffp/alpha_test/ref.hpp>


sge::renderer::state::ffp::alpha_test::enabled::enabled(
	sge::renderer::state::ffp::alpha_test::func const _func,
	sge::renderer::state::ffp::alpha_test::ref const _ref
)
:
	func_(
		_func
	),
	ref_(
		_ref
	)
{
}

sge::renderer::state::ffp::alpha_test::func
sge::renderer::state::ffp::alpha_test::enabled::func() const
{
	return
		func_;
}

sge::renderer::state::ffp::alpha_test::ref
sge::renderer::state::ffp::alpha_test::enabled::ref() const
{
	return
		ref_;
}
