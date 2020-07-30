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
#include <sge/wave/file.hpp>
#include <sge/wave/info.hpp>
#include <fcppt/format.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>
#include <fcppt/endianness/host_format.hpp>
#include <fcppt/endianness/reverse_mem.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <ios>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::wave::file::file(
	fcppt::log::object_reference const _log,
	sge::media::stream_unique_ptr &&_file,
	sge::wave::info const &_info,
	sge::media::optional_name &&_name
)
:
	sge::audio::file(),
	log_{
		_log
	},
	name_(
		std::move(
			_name
		)
	),
	info_(
		_info
	),
	file_(
		std::move(
			_file
		)
	),
	data_segment_(
		file_->tellg()
	),
	samples_read_(
		0
	)
{
}

sge::wave::file::~file()
= default;

sge::audio::bits_per_sample
sge::wave::file::bits_per_sample() const
{
	return
		info_.bits_per_sample();
}

sge::audio::sample_rate
sge::wave::file::sample_rate() const
{
	return
		info_.sample_rate();
}

sge::audio::channel_count
sge::wave::file::channels() const
{
	return
		info_.channels();
}

sge::audio::sample_count
sge::wave::file::expected_package_size() const
{
	return
		fcppt::literal<
			sge::audio::sample_count
		>(
			0
		);
}

void
sge::wave::file::reset()
{
	FCPPT_LOG_DEBUG(
		log_.get(),
		fcppt::log::out
			<< FCPPT_TEXT("wave: resetting file")
	)

	file_->seekg(
		data_segment_
	);

	samples_read_ =
		0U;
}

sge::audio::sample_count
sge::wave::file::read(
	sge::audio::sample_count const _sample_count,
	fcppt::reference<
		sge::audio::sample_buffer
	> const _array
)
{
	sge::audio::sample_count const samples_to_read{
		std::min(
			_sample_count,
			info_.samples()
			-
			samples_read_
		)
	};

	if(
		samples_to_read
		==
		fcppt::literal<
			sge::audio::sample_count
		>(
			0
		)
	)
	{
		return
			fcppt::literal<
				sge::audio::sample_count
			>(
				0
			);
	}

	sge::audio::sample_count const bytes_per_sample(
		sge::audio::bytes_per_sample(
			this->bits_per_sample()
		)
	);

	sge::audio::sample_count const bytes_to_read{
		samples_to_read
		*
		this->channels().get()
		*
		bytes_per_sample
	};

	_array.get().resize_write_area(
		fcppt::cast::size<
			sge::audio::sample_buffer::size_type
		>(
			bytes_to_read
		)
	);

	file_->read(
		fcppt::cast::to_char_ptr<
			char *
		>(
			_array.get().write_data()
		),
		fcppt::cast::size<
			std::streamsize
		>(
			fcppt::cast::to_signed(
				_array.get().write_size()
			)
		)
	);

	sge::audio::sample_buffer::size_type const bytes_read{
		fcppt::cast::size<
			sge::audio::sample_buffer::size_type
		>(
			fcppt::cast::to_unsigned(
				file_->gcount()
			)
		)
	};

	if(
		bytes_per_sample
		>
		fcppt::literal<
			sge::audio::sample_count
		>(
			1
		)
		&&
		info_.endianness()
		!=
		fcppt::endianness::host_format()
	)
	{
		for(
			sge::audio::sample_container::pointer data(
				_array.get().write_data()
			);
			// FIXME
			data < _array.get().write_data() + bytes_read;
			data += bytes_per_sample
		)
		{
			fcppt::endianness::reverse_mem(
				data,
				bytes_per_sample
			);
		}
	}

	// TODO(philipp): Make this easier!
	_array.get().written(
		bytes_read
	);

	samples_read_ +=
		samples_to_read;

	// FIXME: What do we do if the file was truncated?
	return
		samples_to_read;
}

sge::audio::sample_container
sge::wave::file::read_all()
{
	sge::audio::sample_count const to_read{
		info_.samples()
		-
		samples_read_
	};

	sge::audio::sample_buffer result{
		to_read
	};

	this->read(
		to_read,
		fcppt::make_ref(
			result
		)
	);

	return
		fcppt::container::buffer::to_raw_vector(
			std::move(
				result
			)
		);
}
