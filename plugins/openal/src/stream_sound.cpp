/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/audio/file.hpp>
#include <sge/audio/sample_buffer.hpp>
#include <sge/audio/sample_container.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/nonpositional_parameters_fwd.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/positional_parameters_fwd.hpp>
#include <sge/openal/al.hpp>
#include <sge/openal/buffer_id.hpp>
#include <sge/openal/file_format.hpp>
#include <sge/openal/multi_buffer_holder.hpp>
#include <sge/openal/stream_sound.hpp>
#include <sge/openal/funcs/buffer_data.hpp>
#include <sge/openal/funcs/get_source_int.hpp>
#include <sge/openal/funcs/source_play.hpp>
#include <sge/openal/funcs/source_queue_buffer.hpp>
#include <sge/openal/funcs/source_queue_buffers.hpp>
#include <sge/openal/funcs/source_unqueue_buffer.hpp>
#include <sge/openal/funcs/source_unqueue_buffers.hpp>
#include <fcppt/const.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/loop.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/loop_break.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/nothing.hpp>
#include <fcppt/optional/object_impl.hpp>


sge::openal::stream_sound::stream_sound(
	fcppt::log::object &_log,
	sge::audio::sound::nonpositional_parameters const &_parameters,
	sge::audio::file &_audio_file
)
:
	stream_sound(
		_log,
		_parameters,
		_audio_file,
		sge::openal::stream_sound::unified_ctor()
	)
{
}

sge::openal::stream_sound::stream_sound(
	fcppt::log::object &_log,
	sge::audio::sound::positional_parameters const &_parameters,
	sge::audio::file &_audio_file
)
:
	stream_sound(
		_log,
		_parameters,
		_audio_file,
		sge::openal::stream_sound::unified_ctor()
	)
{
}

sge::openal::stream_sound::~stream_sound()
{
	this->stop();

	sge::openal::funcs::source_unqueue_buffers(
		this->source_id(),
		sge::openal::funcs::get_source_int(
			this->source_id(),
			AL_BUFFERS_QUEUED
		)
	);
}

void
sge::openal::stream_sound::update()
{
	// We store this here to prevent multithreading issues (what if the
	// source stops playing while we're processing suff further down?
	sge::audio::sound::play_status const current_play_status(
		this->status()
	);

	ALint const processed(
		sge::openal::funcs::get_source_int(
			this->source_id(),
			AL_BUFFERS_PROCESSED
		)
	);

	if(
		processed
		==
		0
	)
	{
		// If no buffers were processed, we can exit right now and don't
		// need to refill any buffers.
		return;
	}

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< processed
			<< FCPPT_TEXT(" buffers processed")
	);

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

	// First, we create a new variable which stores if we've really filled
	// any more buffers. If we haven't, then the sound is stopped because
	// it's the stream's end.
	bool new_data{
		false
	};

	fcppt::algorithm::loop_break(
		fcppt::make_int_range_count(
			processed
		),
		[
			&new_data,
			this
		](
			ALint
		)
		{
			// throw away one buffer from the top (the processed one)
			sge::openal::buffer_id const buffer(
				sge::openal::funcs::source_unqueue_buffer(
					this->source_id()
				)
			);

			if(
				!this->fill_buffer(
					buffer
				)
			)
				return
					fcppt::loop::break_;

			// ...and put the newly filled back in
			sge::openal::funcs::source_queue_buffer(
				this->source_id(),
				buffer
			);

			new_data =
				true;

			return
				fcppt::loop::continue_;
		}
	);

	// Then we check if the source has really stopped (possible underrun)
	if(
		current_play_status
		!=
		sge::audio::sound::play_status::playing
		&&
		new_data
	)
		// And if an underrun occured, play (again)
		sge::openal::funcs::source_play(
			this->source_id()
		);

	// Note that this works for paused sources, too, since paused sounds
	// don't consume any buffers. At least I think so.
}

void
sge::openal::stream_sound::do_play()
{
	// reset file and fill buffers
	if(
		this->status()
		==
		sge::audio::sound::play_status::playing
	)
		return;

	audio_file_.reset();

	for(
		ALuint const id
		:
		buffers_.container()
	)
		this->fill_buffer(
			sge::openal::buffer_id(
				id
			)
		);

	sge::openal::funcs::source_queue_buffers(
		this->source_id(),
		buffers_.container().data(),
		fcppt::cast::size<
			ALsizei
		>(
			fcppt::cast::to_signed(
				buffers_.container().size()
			)
		)
	);

	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::out
			<< FCPPT_TEXT("queued ")
			<< buffers_.container().size()
			<<  FCPPT_TEXT(" buffers")
	);
}

bool
sge::openal::stream_sound::fill_buffer(
	sge::openal::buffer_id const _buffer
)
{
	typedef
	fcppt::optional::object<
		sge::audio::sample_container
	>
	optional_sample_container;

	auto const next_samples(
		[
			this
		]()
		->
		optional_sample_container
		{
			sge::audio::sample_buffer data{
				0u
			};

			sge::audio::sample_count samples_read(
				audio_file_.read(
					buffer_samples_,
					data
				)
			);

			FCPPT_LOG_DEBUG(
				log_,
				fcppt::log::out
					<< FCPPT_TEXT("read ")
					<< samples_read
					<< FCPPT_TEXT(" samples")
			);

			if(
				samples_read
				==
				0u
			)
			{
				FCPPT_LOG_DEBUG(
					log_,
					fcppt::log::out
						<< FCPPT_TEXT("at the end of last buffer")
				);

				// there's nothing more to load, but the sound should be looped? then reset
				// and start from the beginning
				if(
					this->repeat()
					!=
					sge::audio::sound::repeat::loop
				)
					return
						fcppt::optional::nothing{};

				audio_file_.reset();

				samples_read =
					audio_file_.read(
						buffer_samples_,
						data
					);
			}

			return
				fcppt::optional::make(
					fcppt::container::buffer::to_raw_vector(
						std::move(
							data
						)
					)
				);
		}
	);

	return
		fcppt::optional::maybe(
			next_samples(),
			fcppt::const_(
				false
			),
			[
				_buffer,
				this
			](
				sge::audio::sample_container const &_data
			)
			{
				sge::openal::funcs::buffer_data(
					_buffer,
					format_,
					_data.data(),
					fcppt::cast::size<
						ALsizei
					>(
						fcppt::cast::to_signed(
							_data.size()
						)
					),
					fcppt::cast::size<
						ALsizei
					>(
						fcppt::cast::to_signed(
							audio_file_.sample_rate().get()
						)
					)
				);

				return
					true;
			}
		);
}

template<
	typename Parameters
>
sge::openal::stream_sound::stream_sound(
	fcppt::log::object &_log,
	Parameters const &_parameters,
	sge::audio::file &_audio_file,
	sge::openal::stream_sound::unified_ctor
)
:
	sge::openal::source(
		_log,
		_parameters
	),
	log_{
		_log
	},
	audio_file_(
		_audio_file
	),
	buffer_samples_(
		audio_file_.sample_rate().get()
	),
	format_(
		sge::openal::file_format(
			audio_file_
		)
	),
	buffers_(
		audio_file_.expected_package_size()
		?
			fcppt::cast::size<
				sge::openal::multi_buffer_holder::size_type
			>(
				audio_file_.sample_rate().get()
				/
				audio_file_.expected_package_size()
			)
		:
			fcppt::literal<
				sge::openal::multi_buffer_holder::size_type
			>(
				2
			)
	)
{
	FCPPT_LOG_DEBUG(
		_log,
		fcppt::log::out
			<< FCPPT_TEXT("Created ")
			<< buffers_.container().size()
			<< FCPPT_TEXT(" buffers for this audio file (expected package size ")
			<< audio_file_.expected_package_size()
			<< FCPPT_TEXT(", sample rate ")
			<< audio_file_.sample_rate()
			<< FCPPT_TEXT(")")
	);
}
