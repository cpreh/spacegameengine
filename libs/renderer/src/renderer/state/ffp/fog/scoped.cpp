//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/state/ffp/fog/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/fog/object_fwd.hpp>
#include <sge/renderer/state/ffp/fog/scoped.hpp>
#include <fcppt/make_cref.hpp>


sge::renderer::state::ffp::fog::scoped::scoped(
	sge::renderer::context::ffp &_context,
	sge::renderer::state::ffp::fog::object const &_state
)
:
	context_(
		_context
	)
{
	context_.fog_state(
		sge::renderer::state::ffp::fog::const_optional_object_ref(
			fcppt::make_cref(
				_state
			)
		)
	);
}

sge::renderer::state::ffp::fog::scoped::~scoped()
{
	context_.fog_state(
		sge::renderer::state::ffp::fog::const_optional_object_ref()
	);
}
