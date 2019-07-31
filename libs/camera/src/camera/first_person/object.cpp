//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/base.hpp>
#include <sge/camera/has_mutable_coordinate_system.hpp>
#include <sge/camera/has_mutable_projection.hpp>
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/first_person/object.hpp>
#include <sge/camera/first_person/parameters.hpp>
#include <sge/camera/impl/set_pressed_if_appropriate.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/input/mouse/event/axis.hpp>
#include <sge/renderer/vector4.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/matrix/rotation_axis.hpp>
#include <fcppt/math/matrix/vector.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/cross.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/narrow_cast.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/push_back.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::camera::first_person::object::object(
	sge::camera::first_person::parameters const &_params
)
:
	sge::camera::base{},
	sge::camera::is_dynamic{},
	sge::camera::has_mutable_projection{},
	sge::camera::has_mutable_coordinate_system{},
	action_mapping_{
		_params.action_mapping()
	},
	movement_speed_{
		_params.movement_speed()
	},
	mouse_speed_multiplier_{
		_params.mouse_speed_multiplier()
	},
	directions_{
		fcppt::math::vector::null<
			sge::renderer::vector3
		>()
	},
	coordinate_system_{
		_params.coordinate_system()
	},
	projection_matrix_{
		_params.projection_matrix()
	},
	left_pressed_{
		false
	},
	right_pressed_{
		false
	},
	up_pressed_{
		false
	},
	down_pressed_{
		false
	},
	forward_pressed_{
		false
	},
	backward_pressed_{
		false
	}
{
}

FCPPT_PP_POP_WARNING

sge::camera::coordinate_system::object
sge::camera::first_person::object::coordinate_system() const
{
	return
		coordinate_system_;
}

void
sge::camera::first_person::object::update_coordinate_system(
	sge::camera::coordinate_system::object const &_coordinate_system
)
{
	coordinate_system_ =
		_coordinate_system;
}

sge::camera::optional_projection_matrix
sge::camera::first_person::object::projection_matrix() const
{
	return
		projection_matrix_;
}

void
sge::camera::first_person::object::update_projection_matrix(
	sge::camera::projection_matrix const &_projection_matrix
)
{
	projection_matrix_ =
		sge::camera::optional_projection_matrix(
			_projection_matrix
		);
}

void
sge::camera::first_person::object::process_event(
	sge::input::event_base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::variant::dynamic_cast_<
			brigand::list<
				sge::input::keyboard::event::key const,
				sge::input::mouse::event::axis const
			>,
			fcppt::cast::dynamic_fun
		>(
			_event
		),
		[
			this
		](
			auto const &_variant
		)
		{
			fcppt::variant::match(
				_variant,
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
				},
				[
					this
				](
					fcppt::reference<
						sge::input::mouse::event::axis const
					> const _axis_event
				)
				{
					this->mouse_axis_event(
						_axis_event.get()
					);
				}
			);
		}
	);
}

void
sge::camera::first_person::object::update(
	sge::camera::update_duration const _time_delta
)
{
	coordinate_system_.position(
		sge::camera::coordinate_system::position(
			coordinate_system_.position().get() +
			_time_delta.count() *
			movement_speed_.get() *
			(
				coordinate_system_.right().get() * directions_.x() +
				coordinate_system_.up().get() * directions_.y() +
				coordinate_system_.forward().get() * directions_.z()
			)
		)
	);
}

sge::camera::first_person::object::~object()
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
sge::camera::first_person::object::key_event(
	sge::input::keyboard::event::key const &_key_event
)
{
	sge::camera::impl::set_pressed_if_appropriate(
		left_pressed_,
		action_mapping_.left().get(),
		_key_event
	);

	sge::camera::impl::set_pressed_if_appropriate(
		right_pressed_,
		action_mapping_.right().get(),
		_key_event
	);

	sge::camera::impl::set_pressed_if_appropriate(
		up_pressed_,
		action_mapping_.up().get(),
		_key_event
	);

	sge::camera::impl::set_pressed_if_appropriate(
		down_pressed_,
		action_mapping_.down().get(),
		_key_event
	);

	sge::camera::impl::set_pressed_if_appropriate(
		forward_pressed_,
		action_mapping_.forward().get(),
		_key_event
	);

	sge::camera::impl::set_pressed_if_appropriate(
		backward_pressed_,
		action_mapping_.backward().get(),
		_key_event
	);

	directions_ =
		sge::renderer::vector3{
			direction_from_booleans(
				right_pressed_,
				left_pressed_
			),
			direction_from_booleans(
				up_pressed_,
				down_pressed_
			),
			direction_from_booleans(
				forward_pressed_,
				backward_pressed_
			)
		};
}

void
sge::camera::first_person::object::mouse_axis_event(
	sge::input::mouse::event::axis const &_mouse_axis_event
)
{
	sge::renderer::scalar const scaled_axis_value{
		mouse_speed_multiplier_.get()
		*
		fcppt::cast::int_to_float<
			sge::renderer::scalar
		>(
			_mouse_axis_event.value()
		)
	};

	switch(
		_mouse_axis_event.get().code()
	)
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
	sge::renderer::scalar const _scaled_axis_value
)
{
	sge::renderer::vector3 const y_axis(
		0.0f,
		1.0f,
		0.0f
	);

	sge::renderer::matrix4 const rotation_matrix{
		fcppt::math::matrix::rotation_axis(
			_scaled_axis_value,
			y_axis
		)
	};

	sge::renderer::vector4 const widened_forward{
		fcppt::math::vector::push_back(
			coordinate_system_.forward().get(),
			0.f
		)
	};

	sge::renderer::vector4 const rotated_forward{
		rotation_matrix *
		widened_forward
	};

	coordinate_system_.forward(
		sge::camera::coordinate_system::forward(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::math::vector::normalize(
					fcppt::math::vector::narrow_cast<
						sge::renderer::vector3
					>(
						rotated_forward
					)
				)
			)
		)
	);

	coordinate_system_.right(
		sge::camera::coordinate_system::right(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::math::vector::normalize(
					fcppt::math::vector::cross(
						y_axis,
						coordinate_system_.forward().get()
					)
				)
			)
		)
	);

	// No need to normalize here, forward and right have 90 degree angles.
	coordinate_system_.up(
		sge::camera::coordinate_system::up(
			fcppt::math::vector::cross(
				coordinate_system_.forward().get(),
				coordinate_system_.right().get()
			)
		)
	);
}

void
sge::camera::first_person::object::rotate_on_y(
	sge::renderer::scalar const _scaled_axis_value
)
{
	sge::renderer::scalar const epsilon{
		0.1f
	};

	sge::renderer::vector3 const y_axis{
		0.0f,
		1.0f,
		0.0f
	};

	if(
		(fcppt::math::vector::length(
			-y_axis -
			coordinate_system_.forward().get()) < epsilon
			&&
			_scaled_axis_value > 0.0f
		)
		||
		(fcppt::math::vector::length(
			y_axis -
			coordinate_system_.forward().get()) < epsilon
			&&
			_scaled_axis_value < 0.0f
		)
	)
		return;

	sge::renderer::matrix4 const rotation_matrix{
		fcppt::math::matrix::rotation_axis(
			_scaled_axis_value,
			coordinate_system_.right().get()
		)
	};

	sge::renderer::vector4 const widened_forward{
		fcppt::math::vector::push_back(
			coordinate_system_.forward().get(),
			0.f
		)
	};

	sge::renderer::vector4 const rotated_forward{
		rotation_matrix *
		widened_forward
	};

	coordinate_system_.forward(
		sge::camera::coordinate_system::forward(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::math::vector::normalize(
					fcppt::math::vector::narrow_cast<
						sge::renderer::vector3
					>(
						rotated_forward
					)
				)
			)
		)
	);

	coordinate_system_.up(
		sge::camera::coordinate_system::up(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::math::vector::normalize(
					fcppt::math::vector::cross(
						coordinate_system_.forward().get(),
						coordinate_system_.right().get()
					)
				)
			)
		)
	);

	// No need to normalize here
	coordinate_system_.right(
		sge::camera::coordinate_system::right(
			fcppt::math::vector::cross(
				coordinate_system_.up().get(),
				coordinate_system_.forward().get()
			)
		)
	);

}
