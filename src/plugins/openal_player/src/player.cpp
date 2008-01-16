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
#include "../../../raw_vector_impl.hpp"
#include "../../../types.hpp"
#include "../openal_player.hpp"
#include "../openal_nonstream_sound.hpp"
#include "../openal_stream_sound.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include <al.h>
#else
#include <AL/al.h>
#endif

sge::openal::player::player()
{
	device.reset(alcOpenDevice(0));
	if (device.device == 0)
		throw sge::audio_exception("Error opening audio device!");

	context.reset(alcCreateContext(device.device,0));
	if (context.context == 0)
		throw sge::audio_exception("Error creating audio context!");
	
	if (!alcMakeContextCurrent(context.context))
		throw sge::audio_exception("Error selecting context");
}

void sge::openal::player::update()
{
	for (stream_sound_container_type::iterator i = stream_sounds.begin(); i != stream_sounds.end(); ++i)
		(*i)->update();
}

sge::shared_ptr<sge::sound> sge::openal::player::create_nonstream_sound(const shared_ptr<audio_file> _audio_file)
{
	return shared_ptr<sound>(new nonstream_sound(_audio_file,*this));
}

sge::shared_ptr<sge::sound> sge::openal::player::create_stream_sound(const shared_ptr<audio_file> _audio_file)
{
	return shared_ptr<sound>(new stream_sound(_audio_file,*this));
}

void sge::openal::player::check(const std::string &_desc)
{
	ALint error;
	if ((error = alGetError()) != AL_NO_ERROR)
		throw sge::audio_exception("OpenAL error ("+_desc+"): "+boost::lexical_cast<std::string>(error));
}

void sge::openal::player::listener_pos(const sge::math::vector3 &n)
{
	listener_pos_ = n;

	float vec[3] = { n.x(),n.y(),n.z() };
	alListenerfv(AL_POSITION, vec);
}

void sge::openal::player::listener_angle(const sound_angle &n)
{
	listener_angle_ = n;

	float vec[6] = { n.forward.x(),n.forward.y(),n.forward.z(),n.up.x(),n.up.y(),n.up.z() };
	alListenerfv(AL_POSITION, vec);
}

ALuint sge::openal::player::register_nonstream_sound(const shared_ptr<sge::audio_file> _audio_file)
{
 	for (buffer_map_container_type::iterator i = buffer_map_.begin(); i != buffer_map_.end(); ++i)
	{
		if (i->file == &(*_audio_file))
		{
			(i->refcount)++;
			return i->buffer;
		}
	}

	buffer_map n;
	n.file = &(*_audio_file);

	// Buffer erstellen
	alGenBuffers(1, &n.buffer); check("alGenBuffers");

	ALenum format;
	if (_audio_file->bits_per_sample() == 8 && _audio_file->channels() == 1)
		format = AL_FORMAT_MONO8;
	else if (_audio_file->bits_per_sample() == 8 && _audio_file->channels() == 2)
		format = AL_FORMAT_STEREO8;
	else if (_audio_file->bits_per_sample() == 16 && _audio_file->channels() == 1)
		format = AL_FORMAT_MONO16;
	else if (_audio_file->bits_per_sample() == 16 && _audio_file->channels() == 2)
		format = AL_FORMAT_STEREO16;
	else
		throw audio_exception("OpenAL error: Format not supported: "+boost::lexical_cast<std::string>(_audio_file->bits_per_sample())+" bps, "+boost::lexical_cast<std::string>(_audio_file->channels())+" channels");

	audio_file::raw_array_type data;
	_audio_file->read_all(data);
	alBufferData(n.buffer, format, data.data(), static_cast<ALsizei>(data.size()), static_cast<ALsizei>(_audio_file->sample_rate())); check("alGetError");

	n.refcount = 1;

	buffer_map_.push_back(n);
	return n.buffer;
}

void sge::openal::player::unregister_nonstream_sound(const ALuint buffer)
{
 	for (buffer_map_container_type::iterator i = buffer_map_.begin(); i != buffer_map_.end(); ++i)
	{
		if (i->buffer == buffer)
		{
			if (--(i->refcount) == 0)
			{
				alDeleteBuffers(1,&(i->buffer));
				buffer_map_.erase(i);
				break;
			}
		}
	}
}
