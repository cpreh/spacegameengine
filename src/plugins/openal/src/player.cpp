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


#include "../player.hpp"
#include "../nonstream_sound.hpp"
#include "../stream_sound.hpp"
#include "../error.hpp"
#include "../file_format.hpp"
#include "../log.hpp"
#include "../buffer.hpp"
#include <sge/audio/sound.hpp>
#include <sge/audio/pool.hpp>
#include <sge/audio/exception.hpp>
#include <sge/log/headers.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

sge::openal::player::player()
:
	device_(),
	context_(device_)
{
	context_.make_current();
	// set our own speed of sound standard rather than relying on OpenAL
	speed_of_sound(static_cast<audio::unit>(343));

	listener().pos(audio::point::null());
	listener().vel(audio::point::null());
	listener().direction(
		audio::angle(
			audio::point(
				static_cast<audio::unit>(0),
				static_cast<audio::unit>(0),
				static_cast<audio::unit>(1)),
			audio::point(
				static_cast<audio::unit>(0),
				static_cast<audio::unit>(1),
				static_cast<audio::unit>(0))));
}

sge::openal::player::~player()
{}

sge::audio::unit sge::openal::player::speed_of_sound() const
{
	ALfloat dest;
	alGetFloatv(AL_SPEED_OF_SOUND,&dest);
	return static_cast<audio::unit>(dest);
}

void sge::openal::player::speed_of_sound(audio::unit const dest)
{
	alSpeedOfSound(static_cast<ALfloat>(dest));
}

sge::audio::sound_ptr const
sge::openal::player::create_nonstream_sound(
	audio::file_ptr const _audio_file)
{
	return audio::sound_ptr(new nonstream_sound(_audio_file,*this));
}

sge::audio::sound_ptr const
sge::openal::player::create_stream_sound(
	audio::file_ptr const _audio_file)
{
	return audio::sound_ptr(new stream_sound(_audio_file,*this));
}

ALuint sge::openal::player::register_nonstream_sound(
	audio::file_ptr const _audio_file)
{
	BOOST_FOREACH(buffer &b,nonstream_sounds)
	{
		if (&(b.file()) == &(*_audio_file))
		{
			b.add_instance();
			return b.albuffer();
		}
	}

	nonstream_sounds.push_back(new buffer(*_audio_file));
	buffer &buffer = nonstream_sounds.back();

	audio::sample_container data;
	_audio_file->read_all(data);

	SGE_LOG_DEBUG(
		log(),
		log::_1 << SGE_TEXT("creating buffer of size ")
	          << data.size() << SGE_TEXT(" and format ")
						<< file_format(*_audio_file)
						<< SGE_TEXT(" and sample rate ") << _audio_file->sample_rate());

	if (data.empty())
		throw audio::exception(SGE_TEXT("tried to create empty nonstreaming sound, that's not possible!"));

	alBufferData(
		buffer.albuffer(), 
		file_format(*_audio_file), 
		data.data(), 
		static_cast<ALsizei>(data.size()), 
		static_cast<ALsizei>(_audio_file->sample_rate())); SGE_OPENAL_ERROR_CHECK;

	return buffer.albuffer();
}

void sge::openal::player::unregister_nonstream_sound(ALuint const buffer)
{
 	for (nonstream_sound_container::iterator i = nonstream_sounds.begin(); i != nonstream_sounds.end(); ++i)
	{
		if (i->albuffer() != buffer)
			continue;

		if (i->remove_instance())
			nonstream_sounds.erase(i);

		break;
	}
}

sge::audio::listener &
sge::openal::player::listener()
{
	return listener_;
}
