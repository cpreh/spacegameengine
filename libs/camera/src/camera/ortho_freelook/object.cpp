//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/base.hpp>
#include <sge/camera/is_dynamic.hpp>
#include <sge/camera/optional_projection_matrix.hpp>
#include <sge/camera/projection_matrix.hpp>
#include <sge/camera/update_duration.hpp>
#include <sge/camera/coordinate_system/identity.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/impl/set_pressed_if_appropriate.hpp>
#include <sge/camera/ortho_freelook/object.hpp>
#include <sge/camera/ortho_freelook/optional_projection_rectangle.hpp>
#include <sge/camera/ortho_freelook/parameters.hpp>
#include <sge/camera/ortho_freelook/zoom_speed.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/input/mouse/event/axis.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/projection/orthogonal.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/int_to_float.hpp>
#include <fcppt/math/box/stretch_relative.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/list.hpp>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::camera::ortho_freelook::object::object(
	sge::camera::ortho_freelook::parameters const &_params
)
:
	sge::camera::base{},
	sge::camera::is_dynamic{},
	action_mapping_{
		_params.action_mapping()
	},
	current_projection_rectangle_{},
	zoom_speed_{
		_params.zoom_speed()
	},
	pan_speed_{
		_params.pan_speed()
	},
	near_{
		_params.near()
	},
	far_{
		_params.far()
	},
	zoom_in_pressed_{
		false
	},
	zoom_out_pressed_{
		false
	},
	pan_pressed_{
		false
	}
{
}

FCPPT_PP_POP_WARNING

void
sge::camera::ortho_freelook::object::zoom_speed(
	sge::camera::ortho_freelook::zoom_speed const &_zoom_speed
)
{
	zoom_speed_ =
		_zoom_speed;
}

sge::camera::coordinate_system::object
sge::camera::ortho_freelook::object::coordinate_system() const
{
	return
		sge::camera::coordinate_system::identity();
}

sge::camera::optional_projection_matrix
sge::camera::ortho_freelook::object::projection_matrix() const
{
	return
		fcppt::optional::map(
			current_projection_rectangle_,
			[
				this
			](
				sge::renderer::projection::rect const &_projection_rectangle
			)
			{
				return
					sge::camera::projection_matrix(
						sge::renderer::projection::orthogonal(
							_projection_rectangle,
							near_,
							far_
						)
					);
			}
		);
}

void
sge::camera::ortho_freelook::object::process_event(
	sge::input::event_base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::variant::dynamic_cast_<
			metal::list<
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
sge::camera::ortho_freelook::object::update(
	sge::camera::update_duration const _delta
)
{
	if(
		zoom_in_pressed_
		==
		zoom_out_pressed_
	)
		return;

	fcppt::optional::maybe_void(
		current_projection_rectangle_,
		[
			this,
			_delta
		](
			sge::renderer::projection::rect const &_current_projection_rectangle
		)
		{
			sge::renderer::vector2 const
				ones{
					1.0f,
					1.0f
				},
				scaled_zoom_speed{
					_delta.count() * zoom_speed_.get()
				};

			auto const bool_to_scalar(
				[](
					bool const _value
				)
				-> sge::renderer::scalar
				{
					return
						_value
						?
							1.f
						:
							0.f
						;
				}
			);

			sge::renderer::scalar const zoom_sign{
				bool_to_scalar(
					zoom_out_pressed_
				)
				-
				bool_to_scalar(
					zoom_in_pressed_
				)
			};

			sge::renderer::vector2 const
				zoom_factor{
					ones +
					zoom_sign * scaled_zoom_speed
				};

			current_projection_rectangle_ =
				sge::camera::ortho_freelook::optional_projection_rectangle(
					fcppt::math::box::stretch_relative(
						_current_projection_rectangle,
						zoom_factor
					)
				);
		}
	);
}

void
sge::camera::ortho_freelook::object::projection_rectangle(
	sge::renderer::projection::rect const &_current_projection_rectangle
)
{
	current_projection_rectangle_ =
		sge::camera::ortho_freelook::optional_projection_rectangle(
			_current_projection_rectangle
		);
}

sge::camera::ortho_freelook::object::~object()
{
}

void
sge::camera::ortho_freelook::object::mouse_axis_event(
	sge::input::mouse::event::axis const &_axis
)
{
	if(
		!pan_pressed_
	)
		return;

	if(
		_axis.code()
		!=
		input::mouse::axis_code::x
		&&
		_axis.code()
		!=
		input::mouse::axis_code::y
	)
		return;

	fcppt::optional::maybe_void(
		current_projection_rectangle_,
		[
			&_axis,
			this
		](
			sge::renderer::projection::rect &_current_projection_rectangle
		){
			auto const axis_to_float(
				[
					&_axis
				](
					sge::input::mouse::axis_code const _code
				)
				{
					return
						_axis.code()
						==
						_code
						?
							-fcppt::cast::int_to_float<
								sge::renderer::scalar
							>(
								_axis.value()
							)
						:
							fcppt::literal<
								sge::renderer::scalar
							>(
								0
							)
						;
				}
			);

			sge::renderer::vector2 const
				pan_axis{
					axis_to_float(
						sge::input::mouse::axis_code::x
					),
					axis_to_float(
						sge::input::mouse::axis_code::y
					)
				},
				panning_speed(
					pan_speed_.get() *
					pan_axis *
					_current_projection_rectangle.size()
				);

			_current_projection_rectangle =
				sge::renderer::projection::rect(
					_current_projection_rectangle.pos()
					+
					panning_speed,
					_current_projection_rectangle.size()
				);
		}
	);
}

void
sge::camera::ortho_freelook::object::key_event(
	sge::input::keyboard::event::key const &_key_event
)
{
	sge::camera::impl::set_pressed_if_appropriate(
		zoom_in_pressed_,
		action_mapping_.zoom_in().get(),
		_key_event
	);

	sge::camera::impl::set_pressed_if_appropriate(
		zoom_out_pressed_,
		action_mapping_.zoom_out().get(),
		_key_event
	);

	sge::camera::impl::set_pressed_if_appropriate(
		pan_pressed_,
		action_mapping_.activate_pan().get(),
		_key_event
	);
}
