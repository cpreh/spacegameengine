/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <fcppt/assert/pre.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <sge/camera/ortho_freelook/object.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/ortho_freelook/parameters.hpp>
#include <sge/renderer/vector2.hpp>
#include <fcppt/math/matrix/object_impl.hpp>
#include <fcppt/math/box/stretch_absolute.hpp>

sge::camera::ortho_freelook::object::object(
	ortho_freelook::parameters const &_params)
:
	base_projection_rectangle_(),
	current_projection_rectangle_(),
	zoom_speed_(
		_params.zoom_speed()),
	pan_speed_(
		_params.pan_speed()),
	near_(
		_params.near()),
	far_(
		_params.far()),
	is_active_(
		_params.is_active().get())
{
}

sge::camera::coordinate_system::object const
sge::camera::ortho_freelook::object::coordinate_system() const
{
	return
		sge::camera::coordinate_system::identity();
}

sge::camera::projection_matrix const
sge::camera::ortho_freelook::object::projection_matrix() const
{
	FCPPT_ASSERT_PRE(
		base_projection_rectangle_);

	return
		sge::camera::projection_matrix(
			renderer::projection::orthogonal(
				current_projection_rectangle_,
				near_,
				far_));
}

bool
sge::camera::ortho_freelook::object::is_active() const
{
	return
		is_active_;
}

void
sge::camera::ortho_freelook::object::is_active(
	bool const _is_active)
{
	is_active_ =
		_is_active;
}

void
sge::camera::ortho_freelook::object::projection_rectangle(
	renderer::projection::rect const &_base_projection_rectangle)
{
	base_projection_rectangle_ =
		ortho_freelook::optional_projection_rectangle(
			_base_projection_rectangle);
	current_projection_rectangle_ =
		_base_projection_rectangle;
}

sge::camera::ortho_freelook::object::~object()
{
}

void
sge::camera::ortho_freelook::object::mouse_axis_callback(
	sge::input::mouse::axis_event const &_axis)
{
	if(!base_projection_rectangle_)
		return;

	sge::renderer::vector2 const zoom_speed_factor(
		fcppt::math::dim::structure_cast<sge::renderer::vector2>(
			current_projection_rectangle_.size()) /
		fcppt::math::dim::structure_cast<sge::renderer::vector2>(
			base_projection_rectangle_->size()));

	sge::renderer::vector2 delta_vector =
		sge::renderer::vector2::null();

	switch(_axis.code())
	{
		case sge::input::mouse::axis_code::unknown:
			break;
		case sge::input::mouse::axis_code::x:
			delta_vector.x() =
				static_cast<sge::renderer::scalar>(
					_axis.value());
			break;
		case sge::input::mouse::axis_code::y:
			delta_vector.y() =
				static_cast<sge::renderer::scalar>(
					_axis.value());
			break;
		case sge::input::mouse::axis_code::wheel:
			current_projection_rectangle_ =
				fcppt::math::box::stretch_absolute(
					current_projection_rectangle_,
					sge::renderer::vector2(
						zoom_speed_.get(),
						zoom_speed_.get()));
			break;
	}

	current_projection_rectangle_.pos(
		current_projection_rectangle_.pos() +
		delta_vector *
		zoom_speed_factor *
		sge::renderer::vector2(
			pan_speed_.get(),
			pan_speed_.get()));
}
