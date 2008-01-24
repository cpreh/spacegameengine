/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <string>
#include <boost/lexical_cast.hpp>
#include "../../../audio/audio_player/sound.hpp"
#include "../../../audio/audio_exception.hpp"
#include "../../../types.hpp"
#include "../openal_player.hpp"
#include "../openal_nonstream_sound.hpp"
#include "../openal_stream_sound.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include <al.h>
#else
#include <AL/al.h>
#endif

void sge::openal::nonstream_sound::check(const string &_desc)
{
	ALint error;
	if ((error = alGetError()) != AL_NO_ERROR)
		throw sge::audio_exception(SGE_TEXT("OpenAL error (") +_desc + SGE_TEXT("): ") + boost::lexical_cast<string>(error));
}

sge::openal::nonstream_sound::nonstream_sound(const shared_ptr<sge::audio_file> _audio_file,openal::player &_player) : player_(_player)
{
	al_buffer_ = _player.register_nonstream_sound(_audio_file);

	// Source erstellen
	alGenSources(1,&al_source_); check(SGE_TEXT("alGenSources"));
	alSourcei(al_source_, AL_BUFFER, al_buffer_); check(SGE_TEXT("alSourcei"));

	status_ = status_stopped;
}

void sge::openal::nonstream_sound::play(const bool _loop)
{
	sync();

	loop_ = _loop;
	alSourcei(al_source_,AL_LOOPING,loop_ ? AL_TRUE : AL_FALSE);
	if (status_ == status_playing)
		return;

	alSourcePlay(al_source_);
	status_ = status_playing;
}

void sge::openal::nonstream_sound::stop()
{
	sync();

	// Wenn nicht gestoppt werden muss
	if (status_ == status_stopped)
		return;

	alSourceStop(al_source_);
	status_ = status_stopped;
}

// Achtung! toggle_pause schaltet nur von playing auf paused und von paused auf playing um, nichts anderes!
void sge::openal::nonstream_sound::toggle_pause()
{
	sync();

	if (status_ == status_stopped)
		return;

	if (status_ == status_paused)
	{
		alSourcei(al_source_,AL_LOOPING,loop_ ? AL_TRUE : AL_FALSE);
		alSourcePlay(al_source_);
	}
	else
	{
		alSourcePause(al_source_);
	}
}

sge::openal::nonstream_sound::~nonstream_sound()
{
	player_.unregister_nonstream_sound(al_buffer_);
}

void sge::openal::nonstream_sound::sync() const
{
	ALint play;
	alGetSourcei(al_source_, AL_SOURCE_STATE, &play);
	if (play == AL_STOPPED)
		status_ = status_stopped;
	else if (play == AL_PAUSED)
		status_ = status_paused;
	else if (play == AL_PLAYING)
		status_ = status_playing;
}

void sge::openal::nonstream_sound::positional(const bool n)
{
	positional_ = n;

	if (!n)
	{
		alSourcef(al_source_,AL_ROLLOFF_FACTOR,0.0);
		alSourcei(al_source_,AL_SOURCE_RELATIVE, AL_TRUE);
	}
	else
	{
		alSourcef(al_source_,AL_ROLLOFF_FACTOR,1.0);
		alSourcei(al_source_,AL_SOURCE_RELATIVE, AL_FALSE);
	}
}

void sge::openal::nonstream_sound::pos(const sge::math::vector3 &n)
{
	pos_ = n;

	float vec[3] = { n.x(),n.y(),n.z() };
	alSourcefv(al_source_,AL_POSITION,vec);
}

sge::sound::sound_status sge::openal::nonstream_sound::status() const
{
	sync();
	return status_;
}
