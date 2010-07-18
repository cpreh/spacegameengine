#include <sge/audio/sound/positional_parameters.hpp>

sge::audio::sound::positional_parameters::positional_parameters()
:
	position_(
		vector::null()),
	linear_velocity_(
		vector::null()),
	attenuation_(
		static_cast<scalar>(
			1)),
	rolloff_(
		static_cast<scalar>(
			1)),
	// setting the direction vector to zero creates a non-directional source.
	// this, of course, assumes that the zero vector is uniquely identified by
	// (0.0f,0.0f,0.0f) which is not really guaranteed
	direction_(
		vector::null()),
	inner_cone_angle_(
		static_cast<scalar>(
			360)),
	outer_cone_angle_(
		static_cast<scalar>(
			360))
{
}

sge::audio::vector const &
sge::audio::sound::positional_parameters::position() const
{
	return position_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::position(
	sge::audio::vector const &_position)
{
	position_ = _position;
	return *this;
}

sge::audio::vector const &
sge::audio::sound::positional_parameters::linear_velocity() const
{
	return linear_velocity_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::linear_velocity(
	sge::audio::vector const &_linear_velocity)
{
	linear_velocity_ = _linear_velocity;
	return *this;
}

sge::audio::scalar const &
sge::audio::sound::positional_parameters::attenuation() const
{
	return attenuation_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::attenuation(
	sge::audio::scalar const &_attenuation)
{
	attenuation_ = _attenuation;
	return *this;
}

sge::audio::scalar const &
sge::audio::sound::positional_parameters::rolloff() const
{
	return rolloff_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::rolloff(
	sge::audio::scalar const &_rolloff)
{
	rolloff_ = _rolloff;
	return *this;
}

sge::audio::vector const &
sge::audio::sound::positional_parameters::direction() const
{
	return direction_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::direction(
	sge::audio::vector const &_direction)
{
	direction_ = _direction;
	return *this;
}

sge::audio::scalar const &
sge::audio::sound::positional_parameters::inner_cone_angle() const
{
	return inner_cone_angle_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::inner_cone_angle(
	sge::audio::scalar const &_inner_cone_angle)
{
	inner_cone_angle_ = _inner_cone_angle;
	return *this;
}

sge::audio::scalar const &
sge::audio::sound::positional_parameters::outer_cone_angle() const
{
	return outer_cone_angle_;
}

sge::audio::sound::positional_parameters &
sge::audio::sound::positional_parameters::outer_cone_angle(
	sge::audio::scalar const &_outer_cone_angle)
{
	outer_cone_angle_ = _outer_cone_angle;
	return *this;
}
