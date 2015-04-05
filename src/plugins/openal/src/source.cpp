/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/audio/scalar.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/optional_direction.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/source.hpp>
#include <sge/openal/source_id.hpp>
#include <sge/openal/to_vector3.hpp>
#include <sge/openal/vector3.hpp>
#include <sge/openal/funcs/get_source_int.hpp>
#include <sge/openal/funcs/source_float.hpp>
#include <sge/openal/funcs/source_float_ptr.hpp>
#include <sge/openal/funcs/source_int.hpp>
#include <sge/openal/funcs/source_pause.hpp>
#include <sge/openal/funcs/source_play.hpp>
#include <sge/openal/funcs/source_stop.hpp>
#include <fcppt/const.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/math/rad_to_deg.hpp>


sge::openal::source::source(
	sge::audio::sound::nonpositional_parameters const &_parameters,
	sge::openal::buffer_id const _buffer
)
:
	source(
		_buffer
	)
{
	this->init(
		_parameters
	);
}

sge::openal::source::source(
	sge::audio::sound::positional_parameters const &_parameters,
	sge::openal::buffer_id const _buffer
)
:
	source(
		_buffer
	)
{
	this->init(
		_parameters
	);
}

sge::openal::source::source(
	sge::audio::sound::nonpositional_parameters const &_parameters
)
:
	source()
{
	this->init(
		_parameters
	);
}

sge::openal::source::source(
	sge::audio::sound::positional_parameters const &_parameters
)
:
	source()
{
	this->init(
		_parameters
	);
}

sge::openal::source::~source()
{
}

void
sge::openal::source::play(
	sge::audio::sound::repeat const _repeat
)
{
	repeat_ =
		_repeat;

	this->do_play();

	if(
		this->status() != sge::audio::sound::play_status::playing
	)
		sge::openal::funcs::source_play(
			this->source_id()
		);
}

void
sge::openal::source::toggle_pause()
{
	switch(
		this->status()
	)
	{
	case sge::audio::sound::play_status::stopped:
		return;
	case sge::audio::sound::play_status::paused:
		sge::openal::funcs::source_play(
			this->source_id()
		);
		return;
	case sge::audio::sound::play_status::playing:
		sge::openal::funcs::source_pause(
			this->source_id()
		);
		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

sge::audio::sound::play_status
sge::openal::source::status() const
{
	switch(
		sge::openal::funcs::get_source_int(
			this->source_id(),
			AL_SOURCE_STATE
		)
	)
	{
		case AL_STOPPED:
		case AL_INITIAL:
			return sge::audio::sound::play_status::stopped;
		case AL_PAUSED:
			return sge::audio::sound::play_status::paused;
		case AL_PLAYING:
			return sge::audio::sound::play_status::playing;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

void
sge::openal::source::stop()
{
	if(
		this->status() == audio::sound::play_status::stopped
	)
		return;

	sge::openal::funcs::source_stop(
		this->source_id()
	);
}

void
sge::openal::source::update()
{
}

void
sge::openal::source::position(
	sge::audio::vector const &_vector
)
{
	sge::openal::funcs::source_float_ptr(
		this->source_id(),
		AL_POSITION,
		sge::openal::to_vector3(
			_vector
		).data()
	);
}

void
sge::openal::source::linear_velocity(
	sge::audio::vector const &_vector
)
{
	sge::openal::funcs::source_float_ptr(
		this->source_id(),
		AL_VELOCITY,
		sge::openal::to_vector3(
			_vector
		).data()
	);
}

void
sge::openal::source::gain(
	sge::audio::scalar const _value
)
{
	sge::openal::funcs::source_float(
		this->source_id(),
		AL_GAIN,
		static_cast<
			ALfloat
		>(
			_value
		)
	);
}

void
sge::openal::source::pitch(
	sge::audio::scalar const _value
)
{
	sge::openal::funcs::source_float(
		this->source_id(),
		AL_PITCH,
		static_cast<
			ALfloat
		>(
			_value
		)
	);
}

void
sge::openal::source::rolloff_factor(
	sge::audio::scalar const _value
)
{
	sge::openal::funcs::source_float(
		this->source_id(),
		AL_ROLLOFF_FACTOR,
		static_cast<
			ALfloat
		>(
			_value
		)
	);
}

void
sge::openal::source::reference_distance(
	sge::audio::scalar const _value
)
{
	sge::openal::funcs::source_float(
		this->source_id(),
		AL_REFERENCE_DISTANCE,
		static_cast<
			ALfloat
		>(
			_value
		)
	);
}

void
sge::openal::source::max_distance(
	sge::audio::scalar const _value
)
{
	sge::openal::funcs::source_float(
		this->source_id(),
		AL_MAX_DISTANCE,
		static_cast<
			ALfloat
		>(
			_value
		)
	);
}

void
sge::openal::source::direction(
	sge::audio::sound::optional_direction const &_opt_dir
)
{
	sge::openal::funcs::source_float_ptr(
		this->source_id(),
		AL_DIRECTION,
		sge::openal::to_vector3(
			fcppt::from_optional(
				_opt_dir,
				fcppt::const_(
					sge::audio::vector::null()
				)
			)
		).data()
	);
}

void
sge::openal::source::inner_cone_angle(
	sge::audio::scalar const _value
)
{
	sge::openal::funcs::source_float(
		this->source_id(),
		AL_CONE_INNER_ANGLE,
		static_cast<
			ALfloat
		>(
			fcppt::math::rad_to_deg(
				_value
			)
		)
	);
}

void
sge::openal::source::outer_cone_angle(
	sge::audio::scalar const _value
)
{
	sge::openal::funcs::source_float(
		this->source_id(),
		AL_CONE_OUTER_ANGLE,
		static_cast<
			ALfloat
		>(
			fcppt::math::rad_to_deg(
				_value
			)
		)
	);
}

void
sge::openal::source::outer_cone_gain(
	sge::audio::scalar const _value
)
{
	sge::openal::funcs::source_float(
		this->source_id(),
		AL_CONE_OUTER_GAIN,
		static_cast<
			ALfloat
		>(
			_value
		)
	);
}

void
sge::openal::source::do_play()
{
	sge::openal::funcs::source_int(
		this->source_id(),
		AL_LOOPING,
		repeat_
		==
		sge::audio::sound::repeat::loop
		?
			AL_TRUE
		:
			AL_FALSE
	);
}

sge::openal::source_id const
sge::openal::source::source_id() const
{
	return source_.get();
}

sge::audio::sound::repeat
sge::openal::source::repeat() const
{
	return repeat_;
}

sge::openal::source::source()
:
	source_(),
	repeat_(
		sge::audio::sound::repeat::once
	)
{
}

sge::openal::source::source(
	sge::openal::buffer_id const _buffer
)
:
	source()
{
	sge::openal::funcs::source_int(
		this->source_id(),
		AL_BUFFER,
		static_cast<
			ALint
		>(
			_buffer.get()
		)
	);
}

// that's a hack because we have two constructors
void
sge::openal::source::init(
	sge::audio::sound::positional_parameters const &_parameters
)
{
	this->pitch(
		_parameters.pitch()
	);

	this->position(
		_parameters.position()
	);

	this->linear_velocity(
		_parameters.linear_velocity()
	);

	this->pitch(
		_parameters.pitch()
	);

	this->gain(
		_parameters.gain()
	);

	this->rolloff_factor(
		_parameters.rolloff_factor()
	);

	this->reference_distance(
		_parameters.reference_distance()
	);

	this->max_distance(
		_parameters.max_distance()
	);

	this->inner_cone_angle(
		_parameters.inner_cone_angle()
	);

	this->outer_cone_angle(
		_parameters.outer_cone_angle()
	);

	this->direction(
		_parameters.direction()
	);
}

void
sge::openal::source::init(
	sge::audio::sound::nonpositional_parameters const &_parameters
)
{
	this->init(
		sge::audio::sound::positional_parameters()
			.gain(
				_parameters.gain()
			)
			.pitch(
				_parameters.pitch()
			)
			// The special value 0 for the rolloff factor means
			// that the source is nonpositional (as indicated
			// directly by the OpenAL spec)
			.rolloff_factor(
				0.0f
			)
	);
}
