/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/renderer/vector4.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/math/matrix/rotation_axis.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/construct.hpp>
#include <fcppt/math/vector/cross.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/narrow_cast.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::camera::first_person::object::object(
	first_person::parameters const &_params)
:
	keyboard_connection_(
		_params.keyboard().key_callback(
			std::bind(
				&object::key_callback,
				this,
				std::placeholders::_1))),
	mouse_axis_connection_(
		_params.mouse().axis_callback(
			std::bind(
				&object::mouse_axis_callback,
				this,
				std::placeholders::_1))),
	action_mapping_(
		_params.action_mapping()),
	movement_speed_(
		_params.movement_speed()),
	mouse_speed_multiplier_(
		_params.mouse_speed_multiplier()),
	is_active_(
		_params.is_active()),
	directions_(
		sge::renderer::vector3::null()),
	coordinate_system_(
		_params.coordinate_system()),
	projection_matrix_(
		_params.projection_matrix()),
	left_pressed_(
		false),
	right_pressed_(
		false),
	up_pressed_(
		false),
	down_pressed_(
		false),
	forward_pressed_(
		false),
	backward_pressed_(
		false)
{
}

FCPPT_PP_POP_WARNING

sge::camera::coordinate_system::object const
sge::camera::first_person::object::coordinate_system() const
{
	return
		coordinate_system_;
}

void
sge::camera::first_person::object::update_coordinate_system(
	sge::camera::coordinate_system::object const &_coordinate_system)
{
	coordinate_system_ =
		_coordinate_system;
}

sge::camera::projection_matrix const
sge::camera::first_person::object::projection_matrix() const
{
	FCPPT_ASSERT_PRE(
		projection_matrix_);

	return
		*projection_matrix_;
}

void
sge::camera::first_person::object::update_projection_matrix(
	camera::projection_matrix const &_projection_matrix)
{
	projection_matrix_ =
		_projection_matrix;
}

sge::camera::is_active const
sge::camera::first_person::object::is_active() const
{
	return
		is_active_;
}

void
sge::camera::first_person::object::is_active(
	sge::camera::is_active const _is_active)
{
	is_active_ =
		_is_active;
}

void
sge::camera::first_person::object::update(
	camera::update_duration const _time_delta)
{
	if(!this->is_active().get())
		return;

	coordinate_system_.position(
		coordinate_system::position(
			coordinate_system_.position().get() +
			_time_delta.count() *
			movement_speed_.get() *
			(
				coordinate_system_.right().get() * directions_.x() +
				coordinate_system_.up().get() * directions_.y() +
				coordinate_system_.forward().get() * directions_.z())));
}

sge::camera::first_person::object::~object()
{
}

namespace
{
sge::renderer::scalar
direction_from_booleans(
	bool const left,
	bool const right)
{
	return
		left && !right
				?
					-1.0f
				:
					right && !left
					?
						1.0f
					:
						0.0f;
}

void
set_pressed_if_appropriate(
	sge::input::keyboard::optional_key_code const &_optional_key,
	bool &b,
	sge::input::keyboard::key_event const &_key_event)
{
	if(_optional_key && (*_optional_key) == _key_event.key_code())
		b = _key_event.pressed();
}
}

void
sge::camera::first_person::object::key_callback(
	sge::input::keyboard::key_event const &_key_event)
{
	set_pressed_if_appropriate(
		action_mapping_.left().get(),
		left_pressed_,
		_key_event);

	set_pressed_if_appropriate(
		action_mapping_.right().get(),
		right_pressed_,
		_key_event);

	set_pressed_if_appropriate(
		action_mapping_.up().get(),
		up_pressed_,
		_key_event);

	set_pressed_if_appropriate(
		action_mapping_.down().get(),
		down_pressed_,
		_key_event);

	set_pressed_if_appropriate(
		action_mapping_.forward().get(),
		forward_pressed_,
		_key_event);

	set_pressed_if_appropriate(
		action_mapping_.backward().get(),
		backward_pressed_,
		_key_event);

	directions_ =
		sge::renderer::vector3(
			direction_from_booleans(
				right_pressed_,
				left_pressed_),
			direction_from_booleans(
				up_pressed_,
				down_pressed_),
			direction_from_booleans(
				forward_pressed_,
				backward_pressed_));
}

void
sge::camera::first_person::object::mouse_axis_callback(
	sge::input::mouse::axis_event const &_mouse_axis_event)
{
	if(!this->is_active().get())
		return;

	sge::renderer::scalar const scaled_axis_value =
		mouse_speed_multiplier_.get() *
		static_cast<sge::renderer::scalar>(
			_mouse_axis_event.value());

	switch(_mouse_axis_event.axis().code())
	{
		case sge::input::mouse::axis_code::x:
			this->rotate_on_x(
				scaled_axis_value);
			break;

		case sge::input::mouse::axis_code::y:
			this->rotate_on_y(
				scaled_axis_value);
			break;
		case sge::input::mouse::axis_code::unknown:
		case sge::input::mouse::axis_code::wheel:
			break;
	}
}

void
sge::camera::first_person::object::rotate_on_x(
	sge::renderer::scalar const scaled_axis_value)
{
	sge::renderer::vector3 const y_axis(
		0.0f,
		1.0f,
		0.0f);

	sge::renderer::matrix4 const rotation_matrix =
		fcppt::math::matrix::rotation_axis(
			scaled_axis_value,
			y_axis);

	sge::renderer::vector4 const widened_forward =
		fcppt::math::vector::construct(
			coordinate_system_.forward().get(),
			static_cast<sge::renderer::scalar>(
				0.0f));

	sge::renderer::vector4 const rotated_forward =
		rotation_matrix *
		widened_forward;

	coordinate_system_.forward(
		camera::coordinate_system::forward(
			fcppt::math::vector::normalize(
				fcppt::math::vector::narrow_cast<sge::renderer::vector3>(
					rotated_forward))));

	coordinate_system_.right(
		camera::coordinate_system::right(
			fcppt::math::vector::normalize(
				fcppt::math::vector::cross(
					y_axis,
					coordinate_system_.forward().get()))));

	// No need to normalize here, forward and right have 90 degree angles.
	coordinate_system_.up(
		camera::coordinate_system::up(
			fcppt::math::vector::cross(
				coordinate_system_.forward().get(),
				coordinate_system_.right().get())));
}

void
sge::camera::first_person::object::rotate_on_y(
	sge::renderer::scalar const scaled_axis_value)
{
	sge::renderer::scalar const epsilon =
		0.1f;

	sge::renderer::vector3 const y_axis(
		0.0f,
		1.0f,
		0.0f);

	if(
		(fcppt::math::vector::length(
			-y_axis -
			coordinate_system_.forward().get()) < epsilon &&
		 scaled_axis_value > 0.0f) ||
		(fcppt::math::vector::length(
			y_axis -
			coordinate_system_.forward().get()) < epsilon &&
		 scaled_axis_value < 0.0f))
		return;


	sge::renderer::matrix4 const rotation_matrix =
		fcppt::math::matrix::rotation_axis(
			scaled_axis_value,
			coordinate_system_.right().get());

	sge::renderer::vector4 const widened_forward =
		fcppt::math::vector::construct(
			coordinate_system_.forward().get(),
			static_cast<sge::renderer::scalar>(
				0.0f));

	sge::renderer::vector4 const rotated_forward =
		rotation_matrix *
		widened_forward;

	coordinate_system_.forward(
		camera::coordinate_system::forward(
			fcppt::math::vector::normalize(
				fcppt::math::vector::narrow_cast<sge::renderer::vector3>(
					rotated_forward))));

	coordinate_system_.up(
		camera::coordinate_system::up(
			fcppt::math::vector::normalize(
				fcppt::math::vector::cross(
					coordinate_system_.forward().get(),
					coordinate_system_.right().get()))));

	// No need to normalize here
	coordinate_system_.right(
		camera::coordinate_system::right(
			fcppt::math::vector::cross(
				coordinate_system_.up().get(),
				coordinate_system_.forward().get())));


}
