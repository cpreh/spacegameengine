//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object_fwd.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <fcppt/make_cref.hpp>


sge::renderer::state::ffp::transform::scoped::scoped(
	sge::renderer::context::ffp &_context,
	sge::renderer::state::ffp::transform::mode const _mode,
	sge::renderer::state::ffp::transform::object const &_object
)
:
	context_(
		_context
	),
	mode_(
		_mode
	)
{
	context_.transform(
		mode_,
		sge::renderer::state::ffp::transform::const_optional_object_ref(
			fcppt::make_cref(
				_object
			)
		)
	);
}

sge::renderer::state::ffp::transform::scoped::~scoped()
{
	context_.transform(
		mode_,
		sge::renderer::state::ffp::transform::const_optional_object_ref()
	);
}
