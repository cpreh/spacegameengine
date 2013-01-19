/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/camera/base.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/state/core/depth_stencil/object.hpp>
#include <sge/renderer/state/core/depth_stencil/object_scoped_ptr.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <sge/renderer/state/core/depth_stencil/scoped.hpp>
#include <sge/renderer/state/ffp/transform/object.hpp>
#include <sge/renderer/state/ffp/transform/object_scoped_ptr.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <sge/renderer/state/ffp/transform/scoped.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/scenic/grid/object.hpp>
#include <sge/scenic/grid/orientation.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


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
	sge::scenic::grid::orientation const _orientation,
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
	sge::renderer::device::ffp &_renderer,
	sge::camera::base const &_camera,
	sge::scenic::grid::orientation const _orientation,
	sge::scenic::grid::rect const &_rect,
	sge::scenic::grid::spacing const &_spacing,
	sge::scenic::grid::distance_to_origin const &_distance_to_origin,
	sge::image::color::any::object const &_color)
:
	renderer_(
		_renderer),
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
	sge::renderer::context::ffp &_context,
	sge::scenic::grid::depth_test const &_depth_test)
{
	if(
		!sge::renderer::target::viewport_size(
			_context.target()).content())
		return;

	sge::renderer::state::core::depth_stencil::object_scoped_ptr const depth_state(
		renderer_.create_depth_stencil_state(
			sge::renderer::state::core::depth_stencil::parameters(
				_depth_test.get()
				?
					sge::renderer::state::core::depth_stencil::depth::variant(
						sge::renderer::state::core::depth_stencil::depth::enabled(
							sge::renderer::state::core::depth_stencil::depth::func::less,
							sge::renderer::state::core::depth_stencil::depth::write_enable(
								true)))
				:
					sge::renderer::state::core::depth_stencil::depth::variant(
						sge::renderer::state::core::depth_stencil::depth::off()),
				sge::renderer::state::core::depth_stencil::stencil::off())));

	sge::renderer::state::core::depth_stencil::scoped const depth_transform(
		_context,
		*depth_state);

	sge::renderer::state::ffp::transform::object_scoped_ptr const projection_state(
		renderer_.create_transform_state(
			sge::renderer::state::ffp::transform::parameters(
				camera_.projection_matrix().get())));

	sge::renderer::state::ffp::transform::object_scoped_ptr const world_state(
		renderer_.create_transform_state(
			sge::renderer::state::ffp::transform::parameters(
				sge::camera::matrix_conversion::world(
					camera_.coordinate_system()))));

	sge::renderer::state::ffp::transform::scoped const projection_transform(
		_context,
		sge::renderer::state::ffp::transform::mode::projection,
		*projection_state);

	sge::renderer::state::ffp::transform::scoped const world_transform(
		_context,
		sge::renderer::state::ffp::transform::mode::world,
		*world_state);

	line_drawer_.render(
		_context);
}

sge::scenic::grid::object::~object()
{
}
