//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/bits_per_sample.hpp>
#include <sge/audio/bytes_per_sample.hpp>
#include <sge/audio/channel_count.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/sample_buffer.hpp>
#include <sge/audio/sample_container.hpp>
#include <sge/audio/sample_count.hpp>
#include <sge/audio/sample_rate.hpp>
#include <sge/media/optional_name.hpp>
#include <sge/media/stream_unique_ptr.hpp>
#include <sge/vorbis/file.hpp>
#include <sge/vorbis/info.hpp>
#include <sge/vorbis/read.hpp>
#include <sge/vorbis/seek.hpp>
#include <sge/vorbis/stream.hpp>
#include <sge/vorbis/stream_unique_ptr.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/buffer/append_from.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::vorbis::file::file(
	fcppt::log::object &_log,
	sge::media::stream_unique_ptr &&_stdstream,
	sge::vorbis::stream_unique_ptr &&_stream,
	sge::media::optional_name const &_name
)
:
	sge::audio::file(),
	log_{
		_log
	},
	name_(
		_name
	),
	stdstream_(
		std::move(
			_stdstream
		)
	),
	stream_(
		std::move(
			_stream
		)
	),
	info_(
		sge::vorbis::info(
			*stream_,
			name_
		)
	)
{
}

sge::audio::sample_count
sge::vorbis::file::read(
	sge::audio::sample_count const _samples,
	fcppt::reference<
		sge::audio::sample_buffer
	> const _buffer
)
{
	sge::audio::sample_count const bytes_per_sample(
		sge::audio::bytes_per_sample(
			this->bits_per_sample()
		)
	);

	sge::audio::sample_count const bytes_to_read{
		_samples
		*
		this->channels().get()
		*
		bytes_per_sample
	};

	// TODO: Make this API less ugly
	sge::audio::sample_buffer::size_type const old_size{
		_buffer.get().read_size()
	};

	_buffer.get() =
		fcppt::container::buffer::append_from(
			std::move(
				_buffer.get()
			),
			bytes_to_read,
			[
				bytes_per_sample,
				this
			](
				sge::audio::sample_buffer::pointer const _data,
				sge::audio::sample_buffer::size_type const _size
			)
			{
				std::size_t const bytes_read(
					sge::vorbis::read(
						log_,
						*stream_,
						name_,
						_data,
						_size
					)
				);

				// FIXME: This might not be true if a file is truncated?
				FCPPT_ASSERT_ERROR(
					bytes_read
					%
					bytes_per_sample
					==
					0u
				);

				return
					bytes_read;
			}
		);

	return
		(
			_buffer.get().read_size()
			-
			old_size
		)
		/
		bytes_per_sample;
}

sge::audio::sample_container
sge::vorbis::file::read_all()
{
	sge::audio::sample_buffer result{
		0u
	};

	while(
		this->read(
			sge::audio::sample_count{
				16u
				*
				4096u
			},
			fcppt::make_ref(
				result
			)
		)
		!=
		sge::audio::sample_count{
			0u
		}
	)
		;

	return
		fcppt::container::buffer::to_raw_vector(
			std::move(
				result
			)
		);
}

sge::audio::channel_count
sge::vorbis::file::channels() const
{
	return
		sge::audio::channel_count{
			fcppt::cast::to_unsigned(
				info_.channels
			)
		};
}

sge::audio::sample_rate
sge::vorbis::file::sample_rate() const
{
	return
		sge::audio::sample_rate{
			fcppt::cast::to_unsigned(
				info_.rate
			)
		};
}

sge::audio::bits_per_sample
sge::vorbis::file::bits_per_sample() const
{
	return
		sge::audio::bits_per_sample{
			16u
		};
}

sge::audio::sample_count
sge::vorbis::file::expected_package_size() const
{
	// FIXME: How do we determine the correct size? :(
	return
		sge::audio::sample_count{
			2048
		};
}

void
sge::vorbis::file::reset()
{
	sge::vorbis::seek(
		*stream_,
		name_,
		0
	);
}

sge::vorbis::file::~file()
{
}
