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


#include <sge/openal/source.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/log.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/sound/nonpositional_parameters.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/rad_to_deg.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::openal::source::source(
	sge::audio::sound::nonpositional_parameters const &p,
	ALuint const _buffer)
:
	source_()
{
	alSourcei(
		source_id(),
		AL_BUFFER,
		static_cast<ALint>(
			_buffer));

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcei failed"),
		audio::exception)

	this->init(
		p);
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

	this->init(
		p);
}

sge::openal::source::source(
	sge::audio::sound::nonpositional_parameters const &p)
:
	source_()
{
	this->init(
		p);
}

sge::openal::source::source(
	audio::sound::positional_parameters const &p)
:
	source_()
{
	this->init(
		p);
}

sge::openal::source::~source()
{
}

void
sge::openal::source::play(
	audio::sound::repeat::type const _repeat)
{
	repeat_ =
		_repeat;

	this->do_play();

	if (this->status() != audio::sound::play_status::playing)
	{
		alSourcePlay(
			source_id());

		SGE_OPENAL_CHECK_STATE(
			FCPPT_TEXT("alSourcePlay failed"),
			audio::exception
		)
	}
}

void
sge::openal::source::toggle_pause()
{
	switch (this->status())
	{
		case audio::sound::play_status::stopped:
			return;
		case audio::sound::play_status::paused:
			alSourcePlay(
				this->source_id());

			SGE_OPENAL_CHECK_STATE(
				FCPPT_TEXT("alSourcePlay failed"),
				audio::exception
			)
		break;
		case audio::sound::play_status::playing:
			alSourcePause(
				this->source_id());

			SGE_OPENAL_CHECK_STATE(
				FCPPT_TEXT("alSourcePause failed"),
				audio::exception
			)
		break;
	}
}

sge::audio::sound::play_status::type
sge::openal::source::status() const
{
	ALint play_mode;

	alGetSourcei(
		this->source_id(),
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
			return audio::sound::play_status::stopped;
		case AL_PAUSED:
			return audio::sound::play_status::paused;
		case AL_PLAYING:
			return audio::sound::play_status::playing;
	}

	FCPPT_ASSERT_UNREACHABLE;
}

void
sge::openal::source::stop()
{
	if (this->status() == audio::sound::play_status::stopped)
		return;

	alSourceStop(
		source_id());

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourceStop failed"),
		audio::exception
	)
}

void
sge::openal::source::update()
{
}

void
sge::openal::source::position(
	audio::vector const &n)
{
	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};

	alSourcefv(
		this->source_id(),
		AL_POSITION,
		vec
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcefv failed"),
		audio::exception
	)
}

void
sge::openal::source::linear_velocity(
	audio::vector const &n)
{
	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};

	alSourcefv(
		this->source_id(),
		AL_VELOCITY,
		vec
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcefv failed"),
		audio::exception
	)
}

void
sge::openal::source::gain(
	audio::scalar const n)
{
	alSourcef(
		this->source_id(),
		AL_GAIN,
		static_cast<ALfloat>(
			n));

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

void
sge::openal::source::pitch(
	audio::scalar const n)
{
	alSourcef(
		this->source_id(),
		AL_PITCH,
		static_cast<ALfloat>(
			n));

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

void
sge::openal::source::rolloff_factor(
	audio::scalar const n)
{
	alSourcef(
		this->source_id(),
		AL_ROLLOFF_FACTOR,
		static_cast<ALfloat>(
			n)
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

void
sge::openal::source::reference_distance(
	audio::scalar const n)
{
	alSourcef(
		this->source_id(),
		AL_REFERENCE_DISTANCE,
		static_cast<ALfloat>(
			n)
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

void
sge::openal::source::max_distance(
	audio::scalar const n)
{
	alSourcef(
		this->source_id(),
		AL_MAX_DISTANCE,
		static_cast<ALfloat>(
			n)
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

void
sge::openal::source::direction(
	audio::sound::optional_direction const &_n)
{
	audio::vector const n =
		_n
		?
			*_n
		:
			audio::vector::null();

	ALfloat const vec[3] =
		{
			static_cast<ALfloat>(n.x()),
			static_cast<ALfloat>(n.y()),
			static_cast<ALfloat>(n.z())
		};

	alSourcefv(
		this->source_id(),
		AL_DIRECTION,
		vec
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcefv failed"),
		audio::exception
	)
}

void
sge::openal::source::inner_cone_angle(
	audio::scalar const n)
{
	alSourcef(
		this->source_id(),
		AL_CONE_INNER_ANGLE,
		static_cast<ALfloat>(
			fcppt::math::rad_to_deg(
				n))
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

void
sge::openal::source::outer_cone_angle(
	audio::scalar const n)
{
	alSourcef(
		this->source_id(),
		AL_CONE_OUTER_ANGLE,
		static_cast<ALfloat>(
			fcppt::math::rad_to_deg(
				n))
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourcef failed"),
		audio::exception
	)
}

void
sge::openal::source::outer_cone_gain(
	audio::scalar const n)
{
	alSourcef(
		this->source_id(),
		AL_CONE_OUTER_GAIN,
		static_cast<ALfloat>(
			n)
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
		this->source_id(),
		AL_LOOPING,
		repeat_ == audio::sound::repeat::loop ? AL_TRUE : AL_FALSE);
}

ALuint
sge::openal::source::source_id() const
{
	return source_.value_;
}

sge::audio::sound::repeat::type
sge::openal::source::repeat() const
{
	return repeat_;
}

// that's a hack because we have two constructors
void
sge::openal::source::init(
	audio::sound::positional_parameters const &p)
{
	this->pitch(
		p.pitch());

	this->position(
		p.position());

	this->linear_velocity(
		p.linear_velocity());

	this->pitch(
		p.pitch());

	this->gain(
		p.gain());

	this->rolloff_factor(
		p.rolloff_factor());

	this->reference_distance(
		p.reference_distance());

	this->max_distance(
		p.max_distance());

	this->inner_cone_angle(
		p.inner_cone_angle());

	this->outer_cone_angle(
		p.outer_cone_angle());

	this->direction(
		p.direction());
}

void
sge::openal::source::init(
	audio::sound::nonpositional_parameters const &p)
{
	this->init(
		audio::sound::positional_parameters()
			.gain(
				p.gain())
			.pitch(
				p.pitch())
			// The special value 0 for the rolloff factor means
			// that the source is nonpositional (as indicated
			// directly by the OpenAL spec)
			.rolloff_factor(
				0.0f));
}
