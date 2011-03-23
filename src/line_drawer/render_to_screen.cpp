#include <sge/line_drawer/render_to_screen.hpp>
#include <sge/line_drawer/object.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/renderer/onscreen_target.hpp>
#include <sge/renderer/viewport.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/math/matrix/orthogonal.hpp>
#include <fcppt/math/matrix/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>

void
sge::line_drawer::render_to_screen(
	sge::renderer::device_ptr const renderer,
	object &drawer)
{
	sge::renderer::scoped_transform projection_scope(
		renderer,
		sge::renderer::matrix_mode::projection,
		fcppt::math::matrix::orthogonal(
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				renderer->onscreen_target()->viewport().get().w()),
			static_cast<sge::renderer::scalar>(
				renderer->onscreen_target()->viewport().get().h()),
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				0),
			static_cast<sge::renderer::scalar>(
				10)));

	sge::renderer::scoped_transform world_scope(
		renderer,
		sge::renderer::matrix_mode::world,
		sge::renderer::matrix4::identity());

	drawer.render();
}
