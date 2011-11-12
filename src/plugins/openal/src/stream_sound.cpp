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


#include <sge/openal/stream_sound.hpp>
#include <sge/openal/openal.hpp>
#include <sge/openal/log.hpp>
#include <sge/openal/check_state.hpp>
#include <sge/openal/file_format.hpp>
#include <sge/audio/exception.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/sound/base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::openal::stream_sound::stream_sound(
	audio::sound::nonpositional_parameters const &p,
	audio::file_ptr const _audio_file)
:
	source(
		p),
	audio_file_(
		_audio_file),
	buffer_samples_(
		static_cast<audio::sample_count>(
			audio_file_->sample_rate())),
	format_(
		openal::file_format(
			*audio_file_)),
	al_buffers_(
		audio_file_->expected_package_size()
		?
			static_cast<buffer_sequence::size_type>(
				audio_file_->sample_rate()/audio_file_->expected_package_size())
		:
			static_cast<buffer_sequence::size_type>(
				2))
{
	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Creating ")
			<< al_buffers_.size()
			<< FCPPT_TEXT(" buffers for this audio file (expected package size ")
			<< audio_file_->expected_package_size()
			<< FCPPT_TEXT(", sample rate ")
			<< audio_file_->sample_rate()
			<< FCPPT_TEXT(")"));

	alGenBuffers(
		static_cast<ALsizei>(
			al_buffers_.size()),
		&al_buffers_[0]);

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
			_audio_file->sample_rate())),
	format_(
		openal::file_format(
			*_audio_file)),
	al_buffers_(
		_audio_file->expected_package_size()
		?
			static_cast<buffer_sequence::size_type>(
				_audio_file->sample_rate()/_audio_file->expected_package_size())
		:
			static_cast<buffer_sequence::size_type>(
				2))
{
	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Creating ")
			<< al_buffers_.size()
			<< FCPPT_TEXT(" buffers for this audio file"));

	alGenBuffers(
		static_cast<ALsizei>(
			al_buffers_.size()),
		&al_buffers_[0]);

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
	// We store this here to prevent multithreading issues (what if the
	// source stops playing while we're processing suff further down?
	audio::sound::play_status::type const current_play_status =
		stream_sound::status();

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
	{
		FCPPT_LOG_DEBUG(
			log(),
			fcppt::log::_ << processed << FCPPT_TEXT(" buffers processed"));
	}
	else
	{
		// If no buffers were processed, we can exit right now and don't
		// need to refill any buffers.
		return;
	}


	// The description for this "hack" comes directly from a Creative Labs guy:
	// http://opensource.creative.com/pipermail/openal/2010-June/012128.html
	//
	// The problem is: If all buffers are processed in one "update" call
	// (which might be the case if we have a long time difference
	// because of lag), OpenAL sets the playing status to
	// "stopped". This stopped is, at first, indistinguishable from the
	// "real" stopped state which you get if you explicitly call
	// "stop()" on the source.
	//
	// See the comments below to see how we hack around this.

	// First, we create a new variable which stores if we've really
	// filled any more buffers. If we haven't, then the sound stopped
	// because it's the stream's end.
	bool new_data = false;
	for(ALint i = 0; i < processed; ++i)
	{
		// TODO: how to handle those errors?
		ALuint buffer;
		// throw away one buffer from the top (the processed one)
		alSourceUnqueueBuffers(
			source_id(),
			static_cast<ALsizei>(1),
			&buffer);

		if(!fill_buffer(buffer))
			break;

		// ...and put the newly filled back in
		alSourceQueueBuffers(
			source_id(),
			static_cast<ALsizei>(1),
			&buffer);
		new_data = true;
	}

	// Then we check if the source has really stopped (possible underrun)
	if(current_play_status != audio::sound::play_status::playing && new_data)
		// And if an underrun occured, play (again)
		alSourcePlay(
			source_id());

	// Note that this works for paused sources, too, since paused sounds
	// don't consume any buffers. At least I think so.
}

void
sge::openal::stream_sound::do_play()
{
	// reset file and fill buffers
	if (status() == audio::sound::play_status::playing)
		return;

	audio_file_->reset();

	std::for_each(
		al_buffers_.begin(),
		al_buffers_.end(),
		std::tr1::bind(
			&stream_sound::fill_buffer,
			this,
			std::tr1::placeholders::_1));

	alSourceQueueBuffers(
		source_id(),
		static_cast<ALsizei>(
			al_buffers_.size()),
		&al_buffers_[0]
	);

	SGE_OPENAL_CHECK_STATE(
		FCPPT_TEXT("alSourceQueueBuffers failed"),
		audio::exception
	)

	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_ << FCPPT_TEXT("queued ") << al_buffers_.size() <<  FCPPT_TEXT(" buffers"));
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
		if (this->repeat() != audio::sound::repeat::loop)
			return false;

		audio_file_->reset();
		samples_read =
			audio_file_->read(
				buffer_samples_,
				data);
	}

	FCPPT_ASSERT_ERROR(
		!data.empty());

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
