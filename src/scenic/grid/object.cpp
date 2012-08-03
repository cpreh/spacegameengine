#include <sge/scenic/grid/object.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/camera/base.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/coordinate_system/object.hpp>

sge::scenic::grid::object::object(
	sge::renderer::device &_renderer,
	sge::camera::base const &_camera,
	sge::scenic::grid::orientation::type const _orientation,
	sge::scenic::grid::rect const &_rect,
	sge::scenic::grid::spacing const &_spacing,
	sge::image::color::any::object const &_color)
:
	camera_(
		_camera),
	line_drawer_(
		_renderer)
{
	sge::line_drawer::scoped_lock llock(
		line_drawer_);

	for(
		sge::renderer::scalar y = _rect.pos()[1];
		y <= _rect.pos()[1] + _rect.size()[1];
		y += _spacing.get()[1])
	{
		switch(_orientation)
		{
			case sge::scenic::grid::orientation::xz:
				llock.value().push_back(
					sge::line_drawer::line(
						sge::renderer::vector3(
							_rect.pos()[0],
							0.0f,
							y),
						sge::renderer::vector3(
							_rect.pos()[0]+_rect.size()[0],
							0.0f,
							y),
						_color,
						_color));
		}
	}

	for(
		sge::renderer::scalar x = _rect.pos()[0];
		x <= _rect.pos()[0] + _rect.size()[0];
		x += _spacing.get()[0])
	{
		switch(_orientation)
		{
			case sge::scenic::grid::orientation::xz:
				llock.value().push_back(
					sge::line_drawer::line(
						sge::renderer::vector3(
							x,
							0.0f,
							_rect.pos()[1]),
						sge::renderer::vector3(
							x,
							0.0f,
							_rect.pos()[1]+_rect.size()[1]),
						_color,
						_color));
		}
	}
}

void
sge::scenic::grid::object::render(
	sge::renderer::context::object &_context,
	sge::scenic::grid::depth_test const &_depth_test)
{
	sge::renderer::state::scoped scoped_state(
		_context,
		sge::renderer::state::list
			(_depth_test.get()
			?
				sge::renderer::state::depth_func::less
			:
				sge::renderer::state::depth_func::off));

	sge::renderer::scoped_transform scoped_world(
		_context,
		sge::renderer::matrix_mode::world,
		sge::camera::matrix_conversion::world(
			camera_.coordinate_system()));

	sge::renderer::scoped_transform scoped_projection(
		_context,
		sge::renderer::matrix_mode::projection,
		camera_.projection_matrix().get());

	line_drawer_.render(
		_context);
}

sge::scenic::grid::object::~object()
{
}
