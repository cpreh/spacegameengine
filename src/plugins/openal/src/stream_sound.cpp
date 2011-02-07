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


#include "../stream_sound.hpp"
#include "../openal.hpp"
#include "../log.hpp"
#include "../check_state.hpp"
#include "../file_format.hpp"
#include <sge/audio/exception.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/file.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert.hpp>

sge::openal::stream_sound::stream_sound(
	audio::file_ptr const _audio_file)
:
	source(),
	audio_file_(
		_audio_file),
	buffer_samples_(
		static_cast<audio::sample_count>(
			2 * _audio_file->sample_rate())),
	format_(
		file_format(
			*_audio_file))
{
	alGenBuffers(
		static_cast<ALsizei>(
			2), 
		al_buffers_);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alGenBuffers failed"),
		audio::exception
	)
}

sge::openal::stream_sound::stream_sound(
	audio::sound::positional_parameters const &p,
	audio::file_ptr const _audio_file)
:
	source(
		p),
	audio_file_(
		_audio_file),
	buffer_samples_(
		static_cast<audio::sample_count>(
			2 * _audio_file->sample_rate())),
	format_(
		file_format(
			*_audio_file))
{
	alGenBuffers(
		static_cast<ALsizei>(
			2), 
		al_buffers_);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alGenBuffers failed"),
		audio::exception
	)
}

sge::openal::stream_sound::~stream_sound()
{
}

void 
sge::openal::stream_sound::update()
{
	sync();

	// TODO: split this!
	ALint processed;
	alGetSourcei(
		source_id(), 
		AL_BUFFERS_PROCESSED, 
		&processed);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("stream_sound::update failed"),
		audio::exception
	)

	if (processed)
		FCPPT_LOG_DEBUG(
			log(),
			fcppt::log::_ << processed << FCPPT_TEXT(" buffers processed"));

	while(processed--)
	{
		// TODO: how to handle those errors?
		ALuint buffer;
		// throw away one buffer from the top (the processed one)
		alSourceUnqueueBuffers(
			source_id(),
			static_cast<ALsizei>(1),
			&buffer);

		// ...and put the newly filled back in
		if (fill_buffer(buffer))
			alSourceQueueBuffers(
				source_id(),
				static_cast<ALsizei>(1),
				&buffer);
	}
}

void 
sge::openal::stream_sound::do_play()
{
	// reset file and fill buffers
	if (status() == audio::sound::play_status::playing)
		return;

	audio_file_->reset();

	fill_buffer(
		al_buffers_[0]);
	fill_buffer(
		al_buffers_[1]);

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_ << FCPPT_TEXT("queued 2 buffers"));

	alSourceQueueBuffers(
		source_id(),
		static_cast<ALsizei>(
			2),
		al_buffers_
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourceQueueBuffers failed"),
		audio::exception
	)
}

bool 
sge::openal::stream_sound::fill_buffer(
	ALuint const buffer)
{
	audio::sample_container data;
	audio::sample_count samples_read =
		audio_file_->read(
			buffer_samples_, 
			data);

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_ << FCPPT_TEXT("read ") << samples_read << FCPPT_TEXT(" samples"));

	if (samples_read == static_cast<audio::sample_count>(0))
	{
		FCPPT_LOG_DEBUG(
			log(),
			fcppt::log::_ << FCPPT_TEXT("at the end of last buffer"));

		// there's nothing more to load, but the sound should be looped? then reset
		// and start from the beginning
		if (repeat() != audio::sound::repeat::loop)
			return false;

		audio_file_->reset();
		samples_read = 
			audio_file_->read(
				buffer_samples_,
				data);
	}

	FCPPT_ASSERT(
		data.size());

	alBufferData(
		buffer,
		format_,
		data.data(),
		static_cast<ALsizei>(
			data.size()),
		static_cast<ALsizei>(
			audio_file_->sample_rate()));

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alBufferData failed"),
		audio::exception
	)

	return true;
}
