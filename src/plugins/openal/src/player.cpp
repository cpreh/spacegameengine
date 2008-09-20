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
#include <sge/audio/sound.hpp>
#include <sge/audio/exception.hpp>
#include <sge/log/headers.hpp>
#include <sge/ptr_container_erase.hpp>
#include <sge/raw_vector_impl.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

sge::openal::player::player()
	: device(),
	  context(device)
{
	context.make_current();
}

void sge::openal::player::update()
{
	BOOST_FOREACH(stream_sound &s,stream_sounds)
		s.update();
}

void sge::openal::player::register_stream_sound(stream_sound *p)
{
	stream_sounds.push_back(p);
}

void sge::openal::player::unregister_stream_sound(stream_sound * const p)
{
	ptr_container_erase(stream_sounds,p);
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
	BOOST_FOREACH(buffer_wrapper &b,nonstream_sounds)
	{
		if (&(b.file()) == &(*_audio_file))
		{
			b.add_instance();
			return b.buffer();
		}
	}

	nonstream_sounds.push_back(new buffer_wrapper(*_audio_file));
	buffer_wrapper &buffer = nonstream_sounds.back();

	audio::sample_container data;
	_audio_file->read_all(data);
	alBufferData(
		buffer.buffer(), 
		file_format(*_audio_file), 
		data.data(), 
		static_cast<ALsizei>(data.size()), 
		static_cast<ALsizei>(_audio_file->sample_rate())); SGE_OPENAL_ERROR_CHECK;

	return buffer.buffer();
}

void sge::openal::player::unregister_nonstream_sound(ALuint const buffer)
{
 	for (nonstream_sound_container::iterator i = nonstream_sounds.begin(); i != nonstream_sounds.end(); ++i)
	{
		if (i->buffer() != buffer)
			continue;

		if (i->remove_instance())
			nonstream_sounds.erase(i);

		break;
	}
}
