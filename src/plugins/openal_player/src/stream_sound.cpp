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


#include "../../../config.h"
#include <boost/lexical_cast.hpp>
#include "../../../audio/audio_player/sound.hpp"
#include "../../../audio/audio_exception.hpp"
#include "../../../raw_vector_impl.hpp"
#include "../openal_player.hpp"
#include "../openal_nonstream_sound.hpp"
#include "../openal_stream_sound.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include <al.h>
#else
#include <AL/al.h>
#endif

void sge::openal::stream_sound::check(const string &_desc)
{
	ALint error;
	if ((error = alGetError()) != AL_NO_ERROR)
		throw sge::audio_exception(SGE_TEXT("OpenAL error (") +_desc + SGE_TEXT("): ") + boost::lexical_cast<string>(error));
}

void sge::openal::stream_sound::sync() const
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

sge::openal::stream_sound::stream_sound(const shared_ptr<audio_file> _audio_file,openal::player &_player)
	: player_(_player),audio_file_(_audio_file)
{
	_player.register_stream_sound(this);
	alGenBuffers(2, al_buffers_); check(SGE_TEXT("alGenBuffers"));

	// Buffer erstellen
	if (_audio_file->bits_per_sample() == 8 && _audio_file->channels() == 1)
		format_ = AL_FORMAT_MONO8;
	else if (_audio_file->bits_per_sample() == 8 && _audio_file->channels() == 2)
		format_ = AL_FORMAT_STEREO8;
	else if (_audio_file->bits_per_sample() == 16 && _audio_file->channels() == 1)
		format_ = AL_FORMAT_MONO16;
	else if (_audio_file->bits_per_sample() == 16 && _audio_file->channels() == 2)
		format_ = AL_FORMAT_STEREO16;
	else
		throw sge::audio_exception(SGE_TEXT("OpenAL error: Format not supported: ")
		                           + boost::lexical_cast<string>(_audio_file->bits_per_sample())
		                           + SGE_TEXT(" bps, ")
		                           + boost::lexical_cast<string>(_audio_file->channels())
		                           + SGE_TEXT(" channels"));

	// Immer 2 Sekunden im Cache haben
	buffer_samples_ = 2*_audio_file->sample_rate();

	// Source erstellen
	alGenSources(1,&al_source_); check(SGE_TEXT("alGenSources"));

	status_ = status_stopped;
}

sge::openal::stream_sound::~stream_sound()
{
	player_.unregister_stream_sound(this);
}

bool sge::openal::stream_sound::fill_buffer(const ALuint buffer)
{
	audio_file::raw_array_type data;
	audio_file::sample_type samples_read = audio_file_->read(buffer_samples_, data);

	if (samples_read == 0)
	{
		// Nichts mehr nachzuladen, aber es soll geloopt werden? Dann resetten und von vorne nachladen
		if (loop_)
		{
			audio_file_->reset();
			samples_read = audio_file_->read(buffer_samples_,data);
		}
		else
		{
			return false;
		}
	}
	alBufferData(buffer, format_, data.data(), static_cast<ALsizei>(data.size()), static_cast<ALsizei>(audio_file_->sample_rate())); check(SGE_TEXT("alBufferData"));
	return true;
}

void sge::openal::stream_sound::play(const bool _loop)
{
	sync();

	loop_ = _loop;
	alSourcei(al_source_,AL_LOOPING,_loop ? AL_TRUE : AL_FALSE);
	if (status_ == status_playing)
		return;

	// Datei resetten und Puffer fuellen
	audio_file_->reset();
	fill_buffer(al_buffers_[0]);
	fill_buffer(al_buffers_[1]);

	alSourceQueueBuffers(al_source_,2,al_buffers_); check(SGE_TEXT("alSourceQueueBuffers"));
	alSourcePlay(al_source_); check(SGE_TEXT("alSourcePlay"));

	status_ = status_playing;
}

void sge::openal::stream_sound::toggle_pause()
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

void sge::openal::stream_sound::stop()
{
	sync();

	// Wenn nicht gestoppt werden muss
	if (status_ == status_stopped)
		return;

	alSourceStop(al_source_);
	status_ = status_stopped;
}

void sge::openal::stream_sound::update()
{
	ALint play;
	alGetSourcei(al_source_, AL_SOURCE_STATE, &play);
	if (play == AL_STOPPED)
		status_ = status_stopped;

	ALint processed;
	alGetSourcei(al_source_, AL_BUFFERS_PROCESSED, &processed);

	while(processed--)
	{
		ALuint buffer;
		// Unqueuen bewirkt, dass der Puffer von oben weggenommen wird...
		alSourceUnqueueBuffers(al_source_, 1, &buffer); check(SGE_TEXT("alSourceUnqueueBuffers"));
		// ...und Queue bewirkt, dass es hinten angefuegt wird. Genial!
		if (fill_buffer(buffer))
			alSourceQueueBuffers(al_source_, 1, &buffer); check(SGE_TEXT("alSourceQueueBuffers"));
	}
}

void sge::openal::stream_sound::positional(const bool n)
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

void sge::openal::stream_sound::pos(const sge::math::vector3 &n)
{
	pos_ = n;

	float vec[3] = { n.x(),n.y(),n.z() };
	alSourcefv(al_source_,AL_POSITION,vec);
}

sge::sound::sound_status sge::openal::stream_sound::status() const
{
	sync();
	return status_;
}
