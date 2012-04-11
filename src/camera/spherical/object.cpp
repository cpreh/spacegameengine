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


#include <sge/camera/spherical/object.hpp>
#include <sge/camera/spherical/parameters.hpp>
#include <sge/camera/spherical/coordinate_system/null.hpp>
#include <sge/camera/spherical/coordinate_system/to_camera_coordinate_system.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/input/mouse/axis_event.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/renderer/vector4.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/math/pi.hpp>
#include <fcppt/math/matrix/rotation_axis.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/construct.hpp>
#include <fcppt/math/vector/cross.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/narrow_cast.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/tr1/functional.hpp>


sge::camera::spherical::object::object(
	spherical::parameters const &_params)
:
	keyboard_connection_(
		_params.keyboard().key_callback(
			std::tr1::bind(
				&object::key_callback,
				this,
				std::tr1::placeholders::_1))),
	action_mapping_(
		_params.action_mapping()),
	movement_speed_(
		_params.movement_speed()),
	origin_(
		_params.origin()),
	minimum_radius_(
		_params.minimum_radius()),
	maximum_radius_(
		_params.maximum_radius()),
	acceleration_factor_(
		_params.acceleration_factor()),
	damping_factor_(
		_params.damping_factor()),
	is_active_(
		_params.is_active()),
	coordinate_system_(
		_params.coordinate_system()),
	projection_matrix_(
		_params.projection_matrix()),
	acceleration_(
		spherical::coordinate_system::null()),
	velocity_(
		spherical::coordinate_system::null()),
	increase_azimuth_pressed_(
		false),
	decrease_azimuth_pressed_(
		false),
	increase_inclination_pressed_(
		false),
	decrease_inclination_pressed_(
		false),
	increase_radius_pressed_(
		false),
	decrease_radius_pressed_(
		false)
{
}

sge::camera::coordinate_system::object const
sge::camera::spherical::object::coordinate_system() const
{
	return
		spherical::coordinate_system::to_camera_coordinate_system(
			coordinate_system_,
			origin_);
}

sge::camera::projection_matrix const
sge::camera::spherical::object::projection_matrix() const
{
	FCPPT_ASSERT_PRE(
		projection_matrix_);

	return
		*projection_matrix_;
}

void
sge::camera::spherical::object::update_projection_matrix(
	camera::projection_matrix const &_projection_matrix)
{
	projection_matrix_ =
		_projection_matrix;
}

bool
sge::camera::spherical::object::is_active() const
{
	return
		is_active_.get();
}

void
sge::camera::spherical::object::is_active(
	bool const _is_active)
{
	is_active_ =
		spherical::is_active(
			_is_active);
}

void
sge::camera::spherical::object::update(
	camera::update_duration const &_time_delta)
{
	if(!this->is_active())
		return;

	velocity_.azimuth(
		spherical::coordinate_system::azimuth(
			1.0f - (1.0f - damping_factor_.get().azimuth().get()) * _time_delta.count()) *
		(velocity_.azimuth() +
		acceleration_factor_.get().azimuth() *
		acceleration_.azimuth() *
		spherical::coordinate_system::azimuth(
			_time_delta.count())));

	velocity_.inclination(
		spherical::coordinate_system::inclination(
			1.0f - (1.0f - damping_factor_.get().inclination().get()) * _time_delta.count()) *
		(velocity_.inclination() +
		acceleration_factor_.get().inclination() *
		acceleration_.inclination() *
		spherical::coordinate_system::inclination(
			_time_delta.count())));

	velocity_.radius(
		spherical::coordinate_system::radius(
			1.0f - (1.0f - damping_factor_.get().radius().get()) * _time_delta.count()) *
		(velocity_.radius() +
		acceleration_factor_.get().radius() *
		acceleration_.radius() *
		spherical::coordinate_system::radius(
			_time_delta.count())));

	coordinate_system_.radius(
		spherical::coordinate_system::radius(
			fcppt::math::clamp(
				coordinate_system_.radius().get() +
				_time_delta.count() *
				movement_speed_.get().radius().get() *
				velocity_.radius().get(),
				minimum_radius_.get(),
				maximum_radius_.get())));

	coordinate_system_.azimuth(
		spherical::coordinate_system::azimuth(
			coordinate_system_.azimuth().get() +
			_time_delta.count() *
			movement_speed_.get().azimuth().get() *
			velocity_.azimuth().get()));

	sge::renderer::scalar const inclination_epsilon = 0.01f;

	coordinate_system_.inclination(
		spherical::coordinate_system::inclination(
			fcppt::math::clamp(
				coordinate_system_.inclination().get() +
				_time_delta.count() *
				movement_speed_.get().inclination().get() *
				velocity_.inclination().get(),
				-fcppt::math::pi<sge::renderer::scalar>() + inclination_epsilon,
				-inclination_epsilon)));
}

sge::camera::spherical::object::~object()
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
	sge::camera::spherical::action::optional_key_code const &_optional_key,
	bool &b,
	sge::input::keyboard::key_event const &_key_event)
{
	if(_optional_key && (*_optional_key) == _key_event.key_code())
		b = _key_event.pressed();
}
}

void
sge::camera::spherical::object::key_callback(
	sge::input::keyboard::key_event const &_key_event)
{
	set_pressed_if_appropriate(
		action_mapping_.increase_azimuth().get(),
		increase_azimuth_pressed_,
		_key_event);

	set_pressed_if_appropriate(
		action_mapping_.decrease_azimuth().get(),
		decrease_azimuth_pressed_,
		_key_event);

	set_pressed_if_appropriate(
		action_mapping_.increase_inclination().get(),
		increase_inclination_pressed_,
		_key_event);

	set_pressed_if_appropriate(
		action_mapping_.decrease_inclination().get(),
		decrease_inclination_pressed_,
		_key_event);

	set_pressed_if_appropriate(
		action_mapping_.increase_radius().get(),
		increase_radius_pressed_,
		_key_event);

	set_pressed_if_appropriate(
		action_mapping_.decrease_radius().get(),
		decrease_radius_pressed_,
		_key_event);

	acceleration_.azimuth(
		spherical::coordinate_system::azimuth(
			direction_from_booleans(
				increase_azimuth_pressed_,
				decrease_azimuth_pressed_)));

	acceleration_.inclination(
		spherical::coordinate_system::inclination(
			direction_from_booleans(
				increase_inclination_pressed_,
				decrease_inclination_pressed_)));

	acceleration_.radius(
		spherical::coordinate_system::radius(
			direction_from_booleans(
				increase_radius_pressed_,
				decrease_radius_pressed_)));
}
