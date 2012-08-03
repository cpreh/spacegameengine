#include <sge/scenic/grid/object.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/camera/base.hpp>
#include <sge/renderer/state/scoped.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <cstddef>
#include <fcppt/math/size_type.hpp>
#include <iostream>

namespace
{
fcppt::math::size_type const axis_mappings[3][3] =
	{
		{
			// xz
			0u,2u,1u
		},
		{
			// xy
			0u,1u,2u
		},
		{
			// yz
			2u,0u,1u
		}
	};

sge::renderer::vector3
permute_vector_according_to_orientation(
	sge::scenic::grid::orientation::type const _orientation,
	sge::renderer::vector3 const &_input)
{
	sge::renderer::vector3 result;
	std::size_t const orientation =
		static_cast<std::size_t>(
			_orientation);
	result[0] = _input[axis_mappings[orientation][0]];
	result[1] = _input[axis_mappings[orientation][1]];
	result[2] = _input[axis_mappings[orientation][2]];
	return result;
}
}

sge::scenic::grid::object::object(
	sge::renderer::device &_renderer,
	sge::camera::base const &_camera,
	sge::scenic::grid::orientation::type const _orientation,
	sge::scenic::grid::rect const &_rect,
	sge::scenic::grid::spacing const &_spacing,
	sge::scenic::grid::distance_to_origin const &_distance_to_origin,
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
		llock.value().push_back(
			sge::line_drawer::line(
				permute_vector_according_to_orientation(
					_orientation,
					sge::renderer::vector3(
						_rect.pos()[0],
						y,
						_distance_to_origin.get())),
				permute_vector_according_to_orientation(
					_orientation,
					sge::renderer::vector3(
						_rect.pos()[0]+_rect.size()[0],
						y,
						_distance_to_origin.get())),
				_color,
				_color));
	}

	for(
		sge::renderer::scalar x = _rect.pos()[0];
		x <= _rect.pos()[0] + _rect.size()[0];
		x += _spacing.get()[0])
	{
		llock.value().push_back(
			sge::line_drawer::line(
				permute_vector_according_to_orientation(
					_orientation,
					sge::renderer::vector3(
						x,
						_rect.pos()[1],
						_distance_to_origin.get())),
				permute_vector_according_to_orientation(
					_orientation,
					sge::renderer::vector3(
						x,
						_rect.pos()[1]+_rect.size()[1],
						_distance_to_origin.get())),
				_color,
				_color));
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
