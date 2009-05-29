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
#include "../openal.hpp"
#include "../log.hpp"
#include "../sentry.hpp"
#include "../file_format.hpp"
#include <sge/audio/sound.hpp>
#include <sge/audio/exception.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/text.hpp>
#include <sge/assert.hpp>

sge::openal::stream_sound::stream_sound(
	audio::file_ptr const _audio_file,
	player &_player)
:
	player_(_player),
	audio_file_(_audio_file),
	buffer_samples_(
		static_cast<audio::sample_count>(
			2 * _audio_file->sample_rate()
		)
	),
	format_(file_format(*_audio_file))
{
	SGE_OPENAL_SENTRY(
		SGE_TEXT("alGenBuffers failed"),
		audio::exception
	)

	alGenBuffers(static_cast<ALsizei>(2), al_buffers_);
}

bool sge::openal::stream_sound::fill_buffer(ALuint const buffer)
{
	audio::sample_container data;
	audio::sample_count samples_read = 
		audio_file_->read(buffer_samples_, data);
	
	SGE_LOG_DEBUG(log(),log::_1 << "read " << samples_read << " samples");

	if (samples_read == static_cast<audio::sample_count>(0))
	{
		SGE_LOG_DEBUG(log(),log::_1 << "at the end of last buffer");

		// there's nothing more to load, but the sound should be looped? then reset
		// and start from the beginning
		if (play_mode() != audio::play_mode::loop)
			return false;

		audio_file_->reset();
		samples_read = audio_file_->read(buffer_samples_,data);
	}

	SGE_ASSERT(data.size());

	SGE_OPENAL_SENTRY(
		SGE_TEXT("alBufferData failed"),
		audio::exception
	)

	alBufferData(
		buffer, 
		format_, 
		data.data(), 
		static_cast<ALsizei>(data.size()), 
		static_cast<ALsizei>(audio_file_->sample_rate())
	);

	return true;
}

void sge::openal::stream_sound::do_play()
{
	// reset file and fill buffers
	if (status() == audio::sound_status::playing)
		return;

	audio_file_->reset();

	fill_buffer(al_buffers_[0]);
	fill_buffer(al_buffers_[1]);

	SGE_LOG_DEBUG(log(),log::_1 << "queued 2 buffers");

	SGE_OPENAL_SENTRY(
		SGE_TEXT("alSourceQueueBuffers failed"),
		audio::exception
	)

	alSourceQueueBuffers(
		alsource(),
		static_cast<ALsizei>(2),
		al_buffers_
	);
}

void sge::openal::stream_sound::update()
{
	sync();

	// TODO: split this!
	SGE_OPENAL_SENTRY(
		SGE_TEXT("stream_sound::update failed"),
		audio::exception
	)

	ALint processed;
	alGetSourcei(alsource(), AL_BUFFERS_PROCESSED, &processed);

	if (processed)
		SGE_LOG_DEBUG(log(),log::_1 << processed << " buffers processed");

	while(processed--)
	{
		ALuint buffer;
		// throw away one buffer from the top (the processed one)
		alSourceUnqueueBuffers(alsource(),static_cast<ALsizei>(1),&buffer);
		// ...and put the newly filled back in
		if (fill_buffer(buffer))
			alSourceQueueBuffers(alsource(),static_cast<ALsizei>(1),&buffer);
	}
}
