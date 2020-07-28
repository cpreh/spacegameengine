//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/ffp/transform/default_context.hpp>
#include <sge/opengl/state/ffp/transform/object.hpp>
#include <sge/opengl/state/ffp/transform/set.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/optional/maybe.hpp>


void
sge::opengl::state::ffp::transform::set(
	sge::opengl::context::object &_context,
	sge::renderer::state::ffp::transform::mode const _mode,
	sge::renderer::state::ffp::transform::const_optional_object_ref const &_object
)
{
	fcppt::optional::maybe(
		_object,
		[
			&_context
		]()
		{
			return
				fcppt::make_cref(
					sge::opengl::context::use<
						sge::opengl::state::ffp::transform::default_context
					>(
						fcppt::make_ref(
							_context
						),
						fcppt::make_ref(
							_context
						)
					).default_state()
				);
		},
		[](
			fcppt::reference<
				sge::renderer::state::ffp::transform::object const
			> const _transform
		)
		{
			return
				fcppt::make_cref(
					fcppt::cast::static_downcast<
						sge::opengl::state::ffp::transform::object const &
					>(
						_transform.get()
					)
				);
		}
	).get().set(
		_mode
	);
}
