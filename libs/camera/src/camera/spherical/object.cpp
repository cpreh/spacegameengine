/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/impl/set_pressed_if_appropriate.hpp>
#include <sge/camera/spherical/object.hpp>
#include <sge/camera/spherical/parameters.hpp>
#include <sge/camera/spherical/coordinate_system/null.hpp>
#include <sge/camera/spherical/coordinate_system/to_camera_coordinate_system.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/renderer/vector4.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
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
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::camera::spherical::object::object(
	sge::camera::spherical::parameters const &_params
)
:
	sge::camera::base{},
	sge::camera::is_dynamic{},
	sge::camera::has_mutable_projection{},
	action_mapping_{
		_params.action_mapping()
	},
	movement_speed_{
		_params.movement_speed()
	},
	origin_{
		_params.origin()
	},
	minimum_radius_{
		_params.minimum_radius()
	},
	maximum_radius_{
		_params.maximum_radius()
	},
	acceleration_factor_{
		_params.acceleration_factor()
	},
	damping_factor_{
		_params.damping_factor()
	},
	coordinate_system_{
		_params.coordinate_system()
	},
	projection_matrix_{
		_params.projection_matrix()
	},
	acceleration_{
		sge::camera::spherical::coordinate_system::null()
	},
	velocity_{
		sge::camera::spherical::coordinate_system::null()
	},
	increase_azimuth_pressed_{
		false
	},
	decrease_azimuth_pressed_{
		false
	},
	increase_inclination_pressed_{
		false
	},
	decrease_inclination_pressed_{
		false
	},
	increase_radius_pressed_{
		false
	},
	decrease_radius_pressed_{
		false
	}
{
}

FCPPT_PP_POP_WARNING

sge::camera::coordinate_system::object
sge::camera::spherical::object::coordinate_system() const
{
	return
		sge::camera::spherical::coordinate_system::to_camera_coordinate_system(
			coordinate_system_,
			origin_
		);
}

sge::camera::optional_projection_matrix
sge::camera::spherical::object::projection_matrix() const
{
	return
		projection_matrix_;
}

void
sge::camera::spherical::object::update_projection_matrix(
	sge::camera::projection_matrix const &_projection_matrix
)
{
	projection_matrix_ =
		sge::camera::optional_projection_matrix(
			_projection_matrix
		);
}

void
sge::camera::spherical::object::update(
	sge::camera::update_duration const _time_delta
)
{
	velocity_.azimuth(
		sge::camera::spherical::coordinate_system::azimuth(
			1.0f - (
				1.0f - damping_factor_.get().azimuth().get()
			) * _time_delta.count()
		)
		*
		(
			velocity_.azimuth() +
			acceleration_factor_.get().azimuth() *
			acceleration_.azimuth() *
			sge::camera::spherical::coordinate_system::azimuth(
				_time_delta.count()
			)
		)
	);

	velocity_.inclination(
		sge::camera::spherical::coordinate_system::inclination(
			1.0f - (
				1.0f - damping_factor_.get().inclination().get()
			) * _time_delta.count()
		)
		*
		(
			velocity_.inclination() +
			acceleration_factor_.get().inclination() *
			acceleration_.inclination() *
			sge::camera::spherical::coordinate_system::inclination(
				_time_delta.count()
			)
		)
	);

	velocity_.radius(
		sge::camera::spherical::coordinate_system::radius(
			1.0f - (
				1.0f - damping_factor_.get().radius().get()
			) * _time_delta.count()
		)
		*
		(
			velocity_.radius() +
			acceleration_factor_.get().radius() *
			acceleration_.radius() *
			sge::camera::spherical::coordinate_system::radius(
				_time_delta.count()
			)
		)
	);

	coordinate_system_.radius(
		sge::camera::spherical::coordinate_system::radius(
			fcppt::math::clamp(
				coordinate_system_.radius().get() +
				_time_delta.count() *
				movement_speed_.get().radius().get() *
				velocity_.radius().get(),
				minimum_radius_.get(),
				maximum_radius_.get()
			)
		)
	);

	coordinate_system_.azimuth(
		sge::camera::spherical::coordinate_system::azimuth(
			coordinate_system_.azimuth().get() +
			_time_delta.count() *
			movement_speed_.get().azimuth().get() *
			velocity_.azimuth().get()
		)
	);

	sge::renderer::scalar const inclination_epsilon{
		0.01f
	};

	coordinate_system_.inclination(
		sge::camera::spherical::coordinate_system::inclination(
			fcppt::math::clamp(
				coordinate_system_.inclination().get() +
				_time_delta.count() *
				movement_speed_.get().inclination().get() *
				velocity_.inclination().get(),
				-fcppt::math::pi<sge::renderer::scalar>() + inclination_epsilon,
				-inclination_epsilon
			)
		)
	);
}

void
sge::camera::spherical::object::process_event(
	sge::input::event_base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::cast::dynamic<
			sge::input::keyboard::event::key const
		>(
			_event
		),
		[
			this
		](
			fcppt::reference<
				sge::input::keyboard::event::key const
			> const _key_event
		)
		{
			this->key_event(
				_key_event.get()
			);
		}
	);
}

sge::camera::spherical::object::~object()
{
}

namespace
{

sge::renderer::scalar
direction_from_booleans(
	bool const _left,
	bool const _right
)
{
	return
		_left && !_right
		?
			-1.0f
		:
			_right && !_left
			?
				1.0f
			:
				0.0f;
}

}

void
sge::camera::spherical::object::key_event(
	sge::input::keyboard::event::key const &_key_event
)
{
	sge::camera::impl::set_pressed_if_appropriate(
		increase_azimuth_pressed_,
		action_mapping_.increase_azimuth().get(),
		_key_event
	);

	sge::camera::impl::set_pressed_if_appropriate(
		decrease_azimuth_pressed_,
		action_mapping_.decrease_azimuth().get(),
		_key_event
	);

	sge::camera::impl::set_pressed_if_appropriate(
		increase_inclination_pressed_,
		action_mapping_.increase_inclination().get(),
		_key_event
	);

	sge::camera::impl::set_pressed_if_appropriate(
		decrease_inclination_pressed_,
		action_mapping_.decrease_inclination().get(),
		_key_event
	);

	sge::camera::impl::set_pressed_if_appropriate(
		increase_radius_pressed_,
		action_mapping_.increase_radius().get(),
		_key_event
	);

	sge::camera::impl::set_pressed_if_appropriate(
		decrease_radius_pressed_,
		action_mapping_.decrease_radius().get(),
		_key_event
	);

	acceleration_.azimuth(
		sge::camera::spherical::coordinate_system::azimuth(
			direction_from_booleans(
				increase_azimuth_pressed_,
				decrease_azimuth_pressed_
			)
		)
	);

	acceleration_.inclination(
		sge::camera::spherical::coordinate_system::inclination(
			direction_from_booleans(
				increase_inclination_pressed_,
				decrease_inclination_pressed_
			)
		)
	);

	acceleration_.radius(
		sge::camera::spherical::coordinate_system::radius(
			direction_from_booleans(
				increase_radius_pressed_,
				decrease_radius_pressed_
			)
		)
	);
}
