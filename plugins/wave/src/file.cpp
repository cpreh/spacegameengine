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
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/buffer/resize_write_area.hpp>
#include <fcppt/container/buffer/to_raw_vector.hpp>
#include <fcppt/endianness/host_format.hpp>
#include <fcppt/endianness/reverse_mem.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <ios>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::wave::file::file(
	fcppt::log::object &_log,
	sge::media::stream_unique_ptr &&_file,
	sge::wave::info const &_info,
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
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("wave: resetting file")
	);

	file_->seekg(
		data_segment_
	);

	samples_read_ =
		0u;
}

sge::audio::sample_count
sge::wave::file::read(
	sge::audio::sample_count const _sample_count,
	sge::audio::sample_buffer &_array
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
		return
			fcppt::literal<
				sge::audio::sample_count
			>(
				0
			);

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

	_array =
		fcppt::container::buffer::resize_write_area(
			_array,
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
			_array.write_data()
		),
		fcppt::cast::size<
			std::streamsize
		>(
			fcppt::cast::to_signed(
				bytes_to_read
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
		for(
			sge::audio::sample_container::pointer data(
				_array.write_data()
			);
			// FIXME
			data < _array.write_data() + bytes_read;
			data += bytes_per_sample
		)
			fcppt::endianness::reverse_mem(
				data,
				bytes_per_sample
			);

	// TODO: Make this easier!
	_array.written(
		bytes_read
	);

	samples_read_ +=
		samples_to_read;

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
		result
	);

	return
		fcppt::container::buffer::to_raw_vector(
			std::move(
				result
			)
		);
}
