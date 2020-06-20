//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/render_to_screen.hpp>
#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/optional_matrix4.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/orthogonal_viewport.hpp>
#include <sge/renderer/state/ffp/transform/const_optional_object_ref.hpp>
#include <sge/renderer/state/ffp/transform/mode.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/assert/optional_error.hpp>


void
sge::line_drawer::render_to_screen(
	sge::renderer::device::ffp &_render_device,
	sge::renderer::context::ffp &_render_context,
	sge::line_drawer::object &_drawer
)
{
	sge::renderer::state::ffp::transform::object_unique_ptr const projection(
		_render_device.create_transform_state(
			sge::renderer::state::ffp::transform::parameters(
				FCPPT_ASSERT_OPTIONAL_ERROR(
					sge::renderer::projection::orthogonal_viewport(
						_render_context.target().viewport(),
						sge::renderer::projection::near(
							0.F
						),
						sge::renderer::projection::far(
							1.F
						)
					)
				)
			)
		)
	);

	sge::renderer::state::ffp::transform::scoped const projection_scope(
		fcppt::make_ref(
			_render_context
		),
		sge::renderer::state::ffp::transform::mode::projection,
		fcppt::make_cref(
			*projection
		)
	);

	_render_context.transform(
		sge::renderer::state::ffp::transform::mode::world,
		sge::renderer::state::ffp::transform::const_optional_object_ref()
	);

	_drawer.render(
		_render_context
	);
}
