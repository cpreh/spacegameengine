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


#include "../player.hpp"
#include "../nonstream_sound.hpp"
#include "../stream_sound.hpp"
#include "../check_state.hpp"
#include "../file_format.hpp"
#include "../log.hpp"
#include "../buffer.hpp"
#include <sge/audio/sound.hpp>
#include <sge/audio/pool.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/sample_container.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>

sge::openal::player::player()
:
	device_(),
	context_(device_)
{
	context_.make_current();
	// set our own speed of sound standard rather than relying on OpenAL
	speed_of_sound(static_cast<audio::scalar>(343));

	listener().pos(audio::vector::null());
	listener().vel(audio::vector::null());
	listener().direction(
		audio::angle(
			audio::vector(
				static_cast<audio::scalar>(0),
				static_cast<audio::scalar>(0),
				static_cast<audio::scalar>(1)),
			audio::vector(
				static_cast<audio::scalar>(0),
				static_cast<audio::scalar>(1),
				static_cast<audio::scalar>(0))));
}

sge::openal::player::~player()
{}

sge::audio::scalar sge::openal::player::speed_of_sound() const
{
	ALfloat dest;
	alGetFloatv(AL_SPEED_OF_SOUND,&dest);
	return static_cast<audio::scalar>(dest);
}

void sge::openal::player::speed_of_sound(audio::scalar const dest)
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

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("creating buffer of size ")
	        	<< data.size()
			<< FCPPT_TEXT(" and format ")
			<< file_format(*_audio_file)
			<< FCPPT_TEXT(" and sample rate ")
			<< _audio_file->sample_rate());

	if (data.empty())
		throw audio::exception(FCPPT_TEXT("tried to create empty nonstreaming sound, that's not possible!"));

	// TODO: this function is called more than once!
	alBufferData(
		buffer.albuffer(),
		file_format(*_audio_file),
		data.data(),
		static_cast<ALsizei>(data.size()),
		static_cast<ALsizei>(_audio_file->sample_rate()));

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alBufferData failed"),
		audio::exception
	)

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
