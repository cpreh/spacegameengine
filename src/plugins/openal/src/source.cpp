/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../source_functions.hpp"
#include "../check_state.hpp"
#include "../log.hpp"
#include <sge/audio/exception.hpp>
#include <fcppt/text.hpp>

// that's a hack because we have two constructors
void sge::openal::source::init()
{
	// we just impose our default values
	positional(false);
	pos(audio::point::null());
	vel(audio::point::null());
	attenuation(static_cast<audio::unit>(1));
	rolloff(static_cast<audio::unit>(1));
	inner_cone_angle(static_cast<audio::unit>(360));
	outer_cone_angle(static_cast<audio::unit>(360));
	// setting the direction vector to zero creates a non-directional source.
	// this, of course, assumes that the zero vector is uniquely identified by
	// (0.0f,0.0f,0.0f) which is not really guaranteed
	direction(audio::point::null());
}

sge::openal::source::source()
:
	source_(),
	status_(audio::sound_status::stopped),
	pos_(),
	direction_(),
	vel_()
{
	init();
}

sge::openal::source::source(ALuint const buffer)
:
	source_(),
	status_(audio::sound_status::stopped),
	pos_(),
	direction_(),
	vel_()
{
	source_i(
		alsource(),
		AL_BUFFER,
		buffer
	);

	init();
}

void sge::openal::source::sync() const
{
	ALint play;
	alGetSourcei(alsource(), AL_SOURCE_STATE, &play);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alGetSourcei failed"),
		audio::exception
	)

	switch (play)
	{
		case AL_STOPPED:
		case AL_INITIAL:
			status_ = audio::sound_status::stopped;
		return;
		case AL_PAUSED:
			status_ = audio::sound_status::paused;
		return;
		case AL_PLAYING:
			status_ = audio::sound_status::playing;
		return;
	}

	throw audio::exception(
		FCPPT_TEXT("OpenAL error: invalid playing status")
	);
}

void sge::openal::source::play(audio::play_mode::type const _play_mode)
{
	sync();
	play_mode(_play_mode);
	do_play();

	if (status() != audio::sound_status::playing)
	{
		status_ = audio::sound_status::playing;

		source_play(
			alsource()
		);
	}
}

void sge::openal::source::toggle_pause()
{
	sync();

	switch (status_)
	{
		case audio::sound_status::stopped:
			return;
		case audio::sound_status::paused:
			play_mode(play_mode_);

			source_play(
				alsource()
			);
		break;
		case audio::sound_status::playing:
			alSourcePause(alsource());

			SGE_OPENAL_CHECK_STATE(
				FCPPT_TEXT("alSourcePause failed"),
				audio::exception
			)
		break;
	}
}

sge::audio::sound_status::type sge::openal::source::status() const
{
	sync();
	return status_;
}

void sge::openal::source::stop()
{
	sync();

	if (status_ == audio::sound_status::stopped)
		return;

	alSourceStop(alsource());

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourceStop failed"),
		audio::exception
	)

	status_ = audio::sound_status::stopped;
}

void sge::openal::source::outer_cone_angle(audio::unit const n)
{
	outer_cone_angle_ = n;

	source_f(
		alsource(),
		AL_CONE_OUTER_ANGLE,
		static_cast<ALfloat>(outer_cone_angle_)
	);
}

void sge::openal::source::inner_cone_angle(audio::unit const n)
{
	inner_cone_angle_ = n;

	source_f(
		alsource(),
		AL_CONE_INNER_ANGLE,
		static_cast<ALfloat>(inner_cone_angle_)
	);
}

void sge::openal::source::attenuation(audio::unit const n)
{
	attenuation_ = n;

	source_f(
		alsource(),
		AL_GAIN,
		static_cast<ALfloat>(attenuation_)
	);
}

void sge::openal::source::rolloff(audio::unit const n)
{
	rolloff_ = n;

	source_f(
		alsource(),
		AL_ROLLOFF_FACTOR,
		static_cast<ALfloat>(n)
	);
}

void sge::openal::source::pos(audio::point const &n)
{
	pos_ = n;

	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};

	source_fv(
		alsource(),
		AL_POSITION,
		vec
	);
}

void sge::openal::source::direction(audio::point const &n)
{
	direction_ = n;

	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};

	source_fv(
		alsource(),
		AL_DIRECTION,
		vec
	);
}

void sge::openal::source::vel(audio::point const &n)
{
	vel_ = n;

	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};

	source_fv(
		alsource(),
		AL_VELOCITY,
		vec
	);
}

void sge::openal::source::positional(bool const n)
{
	if (n == positional_)
		return;

	positional_ = n;

	if (n)
	{
		rolloff(static_cast<audio::unit>(1));

		source_i(
			alsource(),
			AL_SOURCE_RELATIVE,
			AL_FALSE
		);
	}
	else
	{
		rolloff(static_cast<audio::unit>(0));
		// make source relative to listener and set it's position to (0,0,0), so directly on the listener
		source_i(
			alsource(),
			AL_SOURCE_RELATIVE,
			AL_TRUE
		);

		pos(audio::point::null());
	}
}

void sge::openal::source::play_mode(audio::play_mode::type const pm)
{
	play_mode_ = pm;
}
