//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/position.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/sound/optional_direction.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/config/external_begin.hpp>
#include <limits>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::audio::sound::positional_parameters::positional_parameters(
	sge::audio::position _position
)
:
	position_(
		std::move(
			_position.get()
		)
	),
	linear_velocity_(
		fcppt::math::vector::null<
			sge::audio::vector
		>()
	),
	gain_(
		fcppt::literal<
			sge::audio::scalar
		>(
			1
		)
	),
	pitch_(
		fcppt::literal<
			sge::audio::scalar
		>(
			1
		)
	),
	rolloff_factor_(
		fcppt::literal<
			sge::audio::scalar
		>(
			1
		)
	),
	reference_distance_(
		fcppt::literal<
			sge::audio::scalar
		>(
			1
		)
	),
	max_distance_(
		std::numeric_limits<
			sge::audio::scalar
		>::max()
	),
	direction_(),
	// These values have been taken from the OpenAL spec's defaults
	inner_cone_angle_(
		fcppt::math::twopi<
			sge::audio::scalar
		>()
	),
	outer_cone_angle_(
		fcppt::math::twopi<
			sge::audio::scalar
		>()
	),
	outer_cone_gain_(
		fcppt::literal<
			sge::audio::scalar
		>(
			0
		)
	)
{
}

sge::audio::vector
sge::audio::sound::positional_parameters::position() const
{
	return
		position_;
}

sge::audio::vector
sge::audio::sound::positional_parameters::linear_velocity() const
{
	return
		linear_velocity_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::linear_velocity(
	sge::audio::vector _linear_velocity
)
{
	linear_velocity_ =
		std::move(
			_linear_velocity
		);

	return
		*this;
}

sge::audio::scalar
sge::audio::sound::positional_parameters::pitch() const
{
	return
		pitch_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::pitch(
	sge::audio::scalar const _pitch
)
{
	pitch_ =
		_pitch;

	return
		*this;
}

sge::audio::scalar
sge::audio::sound::positional_parameters::gain() const
{
	return
		gain_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::gain(
	sge::audio::scalar const _gain
)
{
	gain_ =
		_gain;

	return
		*this;
}

sge::audio::scalar
sge::audio::sound::positional_parameters::rolloff_factor() const
{
	return
		rolloff_factor_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::rolloff_factor(
	sge::audio::scalar const _rolloff_factor
)
{
	rolloff_factor_ =
		_rolloff_factor;

	return
		*this;
}

sge::audio::scalar
sge::audio::sound::positional_parameters::reference_distance() const
{
	return
		reference_distance_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::reference_distance(
	sge::audio::scalar const _reference_distance
)
{
	reference_distance_ =
		_reference_distance;

	return
		*this;
}

sge::audio::scalar
sge::audio::sound::positional_parameters::max_distance() const
{
	return
		max_distance_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::max_distance(
	sge::audio::scalar const _max_distance
)
{
	max_distance_ =
		_max_distance;

	return
		*this;
}

sge::audio::sound::optional_direction const &
sge::audio::sound::positional_parameters::direction() const
{
	return
		direction_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::direction(
	sge::audio::vector _direction
)
{
	direction_ =
		sge::audio::sound::optional_direction{
			std::move(
				_direction
			)
		};

	return
		*this;
}

sge::audio::scalar
sge::audio::sound::positional_parameters::inner_cone_angle() const
{
	return
		inner_cone_angle_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::inner_cone_angle(
	sge::audio::scalar const _inner_cone_angle
)
{
	inner_cone_angle_ =
		_inner_cone_angle;

	return
		*this;
}

sge::audio::scalar
sge::audio::sound::positional_parameters::outer_cone_angle() const
{
	return
		outer_cone_angle_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::outer_cone_angle(
	sge::audio::scalar const _outer_cone_angle
)
{
	outer_cone_angle_ =
		_outer_cone_angle;

	return
		*this;
}

sge::audio::scalar
sge::audio::sound::positional_parameters::outer_cone_gain() const
{
	return
		outer_cone_gain_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::outer_cone_gain(
	sge::audio::scalar const _outer_cone_gain
)
{
	outer_cone_gain_ =
		_outer_cone_gain;

	return
		*this;
}
