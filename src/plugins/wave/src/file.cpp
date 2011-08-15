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


#include "../file.hpp"
#include <sge/audio/exception.hpp>
#include <sge/audio/file_exception.hpp>
#include <sge/audio/unsupported_format.hpp>
#include <sge/log/global.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/endianness/is_little_endian.hpp>
#include <fcppt/endianness/copy_swapped.hpp>
#include <fcppt/endianness/swap.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/io/ostringstream.hpp>
#include <fcppt/format.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/text.hpp>
#include <fcppt/move.hpp>
#include <boost/cstdint.hpp>
#include <algorithm>

sge::wave::file::file(
	stream_ptr _file,
	audio::optional_path const &_filename)
:
	filename_(
		_filename),
	swap_(
		boost::logic::indeterminate),
	file_(
		fcppt::move(
			_file))
{
	read_riff();
	read_wave();
}

sge::audio::sample_count
sge::wave::file::bits_per_sample() const
{
	return bits_per_sample_;
}

sge::audio::sample_count
sge::wave::file::sample_rate() const
{
	return sample_rate_;
}

sge::audio::channel_type
sge::wave::file::channels() const
{
	return channels_;
}

sge::audio::sample_count
sge::wave::file::samples() const
{
	return samples_;
}

sge::audio::sample_count
sge::wave::file::expected_package_size() const
{
	return 0;
}

void sge::wave::file::reset()
{
	FCPPT_LOG_DEBUG(
		log::global(),
		fcppt::log::_ << "wave: resetting file");

	file_->seekg(
		data_segment);
	samples_read_ =
		0;
}

sge::audio::sample_count sge::wave::file::read(
	audio::sample_count const _sample_count,
	audio::sample_container &_array)
{
	audio::sample_count const samples_to_read =
		std::min(
			_sample_count,
			static_cast<audio::sample_count>(
				samples_ - samples_read_));

	if(samples_to_read == static_cast<audio::sample_count>(0))
		return 0;

	audio::sample_count const bytes_to_read =
		static_cast<audio::sample_count>(
			samples_to_read * channels() * bytes_per_sample());

	audio::sample_container::size_type old_size =
		_array.size();

	_array.resize_uninitialized(
		static_cast<audio::sample_container::size_type>(
			_array.size() + bytes_to_read));

	audio::sample_container::pointer const old_pos(
		_array.data() + old_size);

	file_->read(
		reinterpret_cast<char*>(
			old_pos),
		bytes_to_read);

	// TODO: replace this with copy_to_host
	if (bytes_per_sample() > static_cast<audio::sample_count>(1) && swap_)
		fcppt::endianness::copy_swapped(
			old_pos,
			_array.data_end(),
			old_pos,
			bytes_per_sample());
		//for (audio::sample_container::pointer i = _array.data() + old_size; i != _array.data_end(); i += bytes_per_sample())
		//	fcppt::endianness::swap(i,bytes_per_sample());

	samples_read_ +=
		samples_to_read;
	return samples_to_read;
}


sge::audio::sample_count sge::wave::file::read_all(audio::sample_container &_array)
{
	return
		read(
			samples_ - samples_read_,_array);
}

void sge::wave::file::read_riff()
{
	std::string const rifftype =
		extract_header(
			FCPPT_TEXT("riff"));

	// Endiankrams
	bool file_bigendian;

	if (rifftype == "RIFF")
		file_bigendian = false;
	else if (rifftype == "RIFX")
		file_bigendian = true;
	else
		throw audio::unsupported_format(
			filename_,
			FCPPT_TEXT("file is not a riff file and thus not a wave file"));

	swap_ = file_bigendian == fcppt::endianness::is_little_endian();

	// throw away riff size
	extract_primitive<boost::uint32_t>(
		FCPPT_TEXT("riff chunk size"));
}

void sge::wave::file::read_wave()
{
	if (extract_header(FCPPT_TEXT("wave")) != "WAVE")
		throw audio::unsupported_format(
			filename_,
			FCPPT_TEXT("file is not a wave file (wave header not present)"));

	ignore_chunks_until("fmt ");

	// ignore format chunk size
	extract_primitive<boost::uint32_t>(FCPPT_TEXT("format chunk size"));

	boost::uint16_t const audio_format =
		extract_primitive<boost::uint16_t>(FCPPT_TEXT("audio format"));

	if (audio_format != static_cast<boost::uint16_t>(1))
		throw audio::unsupported_format(
			filename_,
			(fcppt::format(FCPPT_TEXT("wave file \"%1%\" is not pcm encoded (format code is %2%)"))
					 % filename_ % audio_format).str());

	channels_ = static_cast<audio::channel_type>(
			extract_primitive<boost::uint16_t>(FCPPT_TEXT("channel count")));

	sample_rate_ = static_cast<audio::sample_count>(
		extract_primitive<boost::uint32_t>(FCPPT_TEXT("sample rate")));

	// this is not needed with pcm encoding
	extract_primitive<boost::uint32_t>(FCPPT_TEXT("byte rate"));
	extract_primitive<boost::uint16_t>(FCPPT_TEXT("block alignment"));

	bits_per_sample_ = static_cast<audio::sample_count>(
		extract_primitive<boost::uint16_t>(FCPPT_TEXT("bits per sample")));

	ignore_chunks_until("data");

	boost::uint32_t const data_size =
		extract_primitive<boost::uint32_t>(FCPPT_TEXT("data size"));

	samples_ = static_cast<audio::sample_count>(
		data_size / channels() / bytes_per_sample());

	samples_read_ = static_cast<audio::sample_count>(0);

	data_segment = file_->tellg();
}

void sge::wave::file::ignore_chunks_until(std::string const &desc)
{
	while (extract_header(FCPPT_TEXT("subchunk header")) != desc)
	{
		FCPPT_LOG_INFO(
			log::global(),
			fcppt::log::_ << FCPPT_TEXT("detected unknown subchunk in wave file \"")
			        << filename_
			        << FCPPT_TEXT("\""));

		file_->seekg(
			static_cast<std::streamoff>(
				extract_primitive<boost::uint32_t>(
					FCPPT_TEXT("subchunk size"))),
			std::ios_base::cur);
	}
}

std::string const sge::wave::file::extract_header(fcppt::string const &_desc)
{
	typedef fcppt::container::raw_vector<char> char_vector;

	char_vector::size_type const byte_count =
		static_cast<char_vector::size_type>(4);
	char_vector bytes(byte_count);
	file_->read(&bytes[0],byte_count);
	if (file_->bad())
		throw audio::file_exception(
			filename_,
			FCPPT_TEXT("error while reading header \"")+_desc);
	return std::string(bytes.begin(),bytes.end());
}

template<typename T>
T sge::wave::file::extract_primitive(
	fcppt::string const &_desc)
{
	// FIXME: ASSERT
	FCPPT_ASSERT_ERROR(
		swap_ != boost::logic::indeterminate);

	// TODO: replace this with io::read
	T ret;
	file_->read(
		reinterpret_cast<char *>(&ret), sizeof(T));

	if (file_->bad())
		throw audio::file_exception(
			filename_,
			FCPPT_TEXT("error while reading ")+ _desc);

	return swap_ ? fcppt::endianness::swap(ret) : ret;
}
