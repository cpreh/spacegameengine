/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../source.hpp"
#include "../check_state.hpp"
#include "../log.hpp"
#include <sge/audio/exception.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/scalar.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/output.hpp>

sge::openal::source::source(
	ALuint const _buffer)
:
	source_()
{
	alSourcei(
		source_id(),
		AL_BUFFER,
		static_cast<
			ALint
		>(
			_buffer
		)
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcei failed"),
		audio::exception)

	init(
		audio::sound::positional_parameters());

	positional(
		false);
}

sge::openal::source::source(
	audio::sound::positional_parameters const &p,
	ALuint const _buffer)
:
	source_()
{
	alSourcei(
		source_id(),
		AL_BUFFER,
		static_cast<
			ALint
		>(
			_buffer
		)
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcei failed"),
		audio::exception
	)

	init(
		p);

	positional(
		true);
}

sge::openal::source::source()
:
	source_()
{
	init(
		audio::sound::positional_parameters());

	positional(
		false);
}

sge::openal::source::source(
	audio::sound::positional_parameters const &p)
:
	source_()
{
	init(
		p);

	positional(
		true);
}

sge::openal::source::~source()
{
}

void 
sge::openal::source::play(
	audio::sound::repeat::type const _repeat)
{
	sync();
	repeat_ = _repeat;
	do_play();

	if (status() != audio::sound::play_status::playing)
	{
		alSourcePlay(
			source_id());

		sync();

		SGE_OPENAL_CHECK_STATE(
			FCPPT_TEXT("alSourcePlay failed"),
			audio::exception
		)
	}
}

void 
sge::openal::source::toggle_pause()
{
	sync();

	switch (status_)
	{
		case audio::sound::play_status::stopped:
			return;
		case audio::sound::play_status::paused:
			alSourcePlay(
				source_id());

			SGE_OPENAL_CHECK_STATE(
				FCPPT_TEXT("alSourcePlay failed"),
				audio::exception
			)
		break;
		case audio::sound::play_status::playing:
			alSourcePause(
				source_id());

			SGE_OPENAL_CHECK_STATE(
				FCPPT_TEXT("alSourcePause failed"),
				audio::exception
			)
		break;
	}

	sync();
}

sge::audio::sound::play_status::type 
sge::openal::source::status() const
{
	sync();
	return status_;
}

sge::audio::sound::repeat::type 
sge::openal::source::repeat() const
{
	return repeat_;
}

void 
sge::openal::source::stop()
{
	sync();

	if (status_ == audio::sound::play_status::stopped)
		return;

	alSourceStop(
		source_id());

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourceStop failed"),
		audio::exception
	)

	sync();
}

void 
sge::openal::source::update()
{
}

sge::audio::vector const 
sge::openal::source::position() const
{
	return position_;
}

void 
sge::openal::source::position(
	audio::vector const &n)
{
	position_ = n;

	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};

	alSourcefv(
		source_id(),
		AL_POSITION,
		vec
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcefv failed"),
		audio::exception
	)
}

sge::audio::vector const 
sge::openal::source::linear_velocity() const
{
	return linear_velocity_;
}

void 
sge::openal::source::linear_velocity(
	audio::vector const &n)
{
	linear_velocity_ = n;

	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};

	alSourcefv(
		source_id(),
		AL_VELOCITY,
		vec
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcefv failed"),
		audio::exception
	)
}

sge::audio::scalar 
sge::openal::source::gain() const
{
	return gain_;
}

void 
sge::openal::source::gain(
	audio::scalar const n)
{
	gain_ = n;

	alSourcef(
		source_id(),
		AL_GAIN,
		static_cast<ALfloat>(
			n));

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

sge::audio::scalar 
sge::openal::source::pitch() const
{
	return pitch_;
}

void 
sge::openal::source::pitch(
	audio::scalar const n)
{
	pitch_ = n;

	alSourcef(
		source_id(),
		AL_PITCH,
		static_cast<ALfloat>(
			n));

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

sge::audio::scalar 
sge::openal::source::rolloff() const
{
	return rolloff_;
}

void 
sge::openal::source::rolloff(
	audio::scalar const n)
{
	rolloff_ = 
		n;

	alSourcef(
		source_id(),
		AL_ROLLOFF_FACTOR,
		static_cast<ALfloat>(
			n)
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

sge::audio::vector const 
sge::openal::source::direction() const
{
	return direction_;
}

void 
sge::openal::source::direction(
	audio::vector const &n)
{
	direction_ = n;

	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};

	alSourcefv(
		source_id(),
		AL_DIRECTION,
		vec
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcefv failed"),
		audio::exception
	)
}

sge::audio::scalar 
sge::openal::source::inner_cone_angle() const
{
	return inner_cone_angle_;
}

void 
sge::openal::source::inner_cone_angle(
	audio::scalar const n)
{
	inner_cone_angle_ = n;

	alSourcef(
		source_id(),
		AL_CONE_INNER_ANGLE,
		static_cast<ALfloat>(
			inner_cone_angle_)
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

sge::audio::scalar 
sge::openal::source::outer_cone_angle() const
{
	return outer_cone_angle_;
}

void 
sge::openal::source::outer_cone_angle(
	audio::scalar const n)
{
	outer_cone_angle_ = 
		n;

	alSourcef(
		source_id(),
		AL_CONE_OUTER_ANGLE,
		static_cast<ALfloat>(
			outer_cone_angle_)
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

void
sge::openal::source::do_play()
{
	alSourcei(
		source_id(),
		AL_LOOPING,
		repeat_ == audio::sound::repeat::loop ? AL_TRUE : AL_FALSE);
}

void 
sge::openal::source::sync() const
{
	ALint play_mode;

	alGetSourcei(
		source_id(), 
		AL_SOURCE_STATE, 
		&play_mode
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alGetSourcei failed"),
		audio::exception
	)

	switch (play_mode)
	{
		case AL_STOPPED:
		case AL_INITIAL:
			status_ = audio::sound::play_status::stopped;
			return;
		case AL_PAUSED:
			status_ = audio::sound::play_status::paused;
			return;
		case AL_PLAYING:
			status_ = audio::sound::play_status::playing;
			return;
	}

	throw audio::exception(
		FCPPT_TEXT("OpenAL error: invalid playing status")
	);
}

ALuint
sge::openal::source::source_id() const
{
	return source_.value_;
}

// that's a hack because we have two constructors
void 
sge::openal::source::init(
	audio::sound::positional_parameters const &p)
{
	status_ = 
		audio::sound::play_status::stopped;

	pitch_ = 
		static_cast<audio::scalar>(1.0);
	
	position(
		p.position());

	linear_velocity(
		p.linear_velocity());
	
	gain(
		p.gain());

	rolloff(
		p.rolloff());

	inner_cone_angle(
		p.inner_cone_angle());

	outer_cone_angle(
		p.outer_cone_angle());
	
	direction(
		p.direction());
}

void 
sge::openal::source::positional(
	bool const n)
{
	if (n)
	{
		rolloff(
			static_cast<audio::scalar>(
				1));

		alSourcei(
			source_id(),
			AL_SOURCE_RELATIVE,
			AL_FALSE);

		SGE_OPENAL_CHECK_STATE(
			FCPPT_TEXT("alSourcei failed"),
			audio::exception
		)
	}
	else
	{
		// The special case "rolloff = 0" means that the source is not
		// attenuated by distance.
		rolloff(
			static_cast<audio::scalar>(0));

		alSourcei(
			source_id(),
			AL_SOURCE_RELATIVE,
			AL_FALSE);

		SGE_OPENAL_CHECK_STATE(
			FCPPT_TEXT("alSourcei failed"),
			audio::exception)

		position(
			audio::vector::null());
	}
}
