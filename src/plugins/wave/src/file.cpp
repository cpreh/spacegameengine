/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/log/global.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/endianness/is_little_endian.hpp>
#include <fcppt/endianness/copy_swapped.hpp>
#include <fcppt/endianness/swap.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/io/ostringstream.hpp>
#include <fcppt/format.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <boost/cstdint.hpp>

sge::wave::file::file(
	fcppt::filesystem::path const &filename)
:
	filename_(filename.string()),
	swap_(boost::logic::indeterminate),
	file_(filename_, std::ios_base::binary)
{
	if (!file_.is_open())
		throw audio::exception(
			FCPPT_TEXT("couldn't open wave file \"")+filename_+FCPPT_TEXT("\""));

	read_riff();
	read_wave();
}

fcppt::string const sge::wave::file::to_string() const
{
	fcppt::io::ostringstream ss;
	ss << "bits_per_sample: " << bits_per_sample() << ", "
	   << "sample_rate: " << sample_rate() << ", "
	   << "channels: " << channels() << ", "
	   << "samples: " << samples();
	return ss.str();
}

void sge::wave::file::reset()
{
	FCPPT_LOG_DEBUG(log::global(),fcppt::log::_ << "wave: resetting file");
	file_.seekg(data_segment);
	samples_read_ = static_cast<audio::sample_count>(0);
}

sge::audio::sample_count sge::wave::file::read(
	audio::sample_count const _sample_count,
	audio::sample_container &_array)
{
	audio::sample_count const samples_to_read =
		std::min(_sample_count,samples_ - samples_read_);

	if (samples_to_read == static_cast<audio::sample_count>(0))
		return static_cast<audio::sample_count>(0);

	audio::sample_count const bytes_to_read =
		samples_to_read * channels() * bytes_per_sample();

	audio::sample_container::size_type old_size = _array.size();

	_array.resize_uninitialized(
		static_cast<audio::sample_container::size_type>(
			_array.size() + bytes_to_read));

	audio::sample_container::pointer const old_pos(
		_array.data() + old_size
	);

	file_.read(
		reinterpret_cast<char*>(old_pos),
		bytes_to_read);

	// TODO: replace this with copy_to_host
	if (bytes_per_sample() > static_cast<audio::sample_count>(1) && swap_)
		fcppt::endianness::copy_swapped(
			old_pos,
			_array.data_end(),
			old_pos,
			bytes_per_sample()
		);
		//for (audio::sample_container::pointer i = _array.data() + old_size; i != _array.data_end(); i += bytes_per_sample())
		//	fcppt::endianness::swap(i,bytes_per_sample());

	samples_read_ += samples_to_read;
	return samples_to_read;
}


sge::audio::sample_count sge::wave::file::read_all(audio::sample_container &_array)
{
	return read(samples_ - samples_read_,_array);
}

void sge::wave::file::read_riff()
{
	std::string const rifftype =
		extract_header(FCPPT_TEXT("riff"));

	// Endiankrams
	bool file_bigendian;

	if (rifftype == "RIFF")
		file_bigendian = false;
	else if (rifftype == "RIFX")
		file_bigendian = true;
	else
		throw audio::exception(FCPPT_TEXT("file \"")+filename_+FCPPT_TEXT("\" is not a riff file and thus not a wave file"));

	swap_ = file_bigendian == fcppt::endianness::is_little_endian();

	// throw away riff size
	extract_primitive<boost::uint32_t>(FCPPT_TEXT("riff chunk size"));
}

void sge::wave::file::read_wave()
{
	if (extract_header(FCPPT_TEXT("wave")) != "WAVE")
		throw audio::exception(FCPPT_TEXT("the riff file \"")+filename_+FCPPT_TEXT("\" is not a wave file (wave header not present)"));

	ignore_chunks_until("fmt ");

	// ignore format chunk size
	extract_primitive<boost::uint32_t>(FCPPT_TEXT("format chunk size"));

	boost::uint16_t const audio_format =
		extract_primitive<boost::uint16_t>(FCPPT_TEXT("audio format"));

	if (audio_format != static_cast<boost::uint16_t>(1))
		throw audio::exception(
			(
				fcppt::format(
					FCPPT_TEXT("wave file \"%1%\" is not pcm encoded (format code is %2%)")
				)
				% filename_
				% audio_format
			).str()
		);

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

	data_segment = file_.tellg();
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

		file_.seekg(
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
	file_.read(&bytes[0],byte_count);
	if (file_.bad())
		throw audio::exception(
			FCPPT_TEXT("error while reading header \"")
			+ _desc
			+ FCPPT_TEXT("\" from file \"")
			+ filename_
			+ FCPPT_TEXT("\""));
	return std::string(bytes.begin(),bytes.end());
}

template<typename T>
T sge::wave::file::extract_primitive(fcppt::string const &_desc)
{
	FCPPT_ASSERT(swap_ != boost::logic::indeterminate);

	// TODO: replace this with io::read
	T ret;
	file_.read(
		reinterpret_cast<char *>(&ret), sizeof(T)
	);

	if (file_.bad())
		throw audio::exception(
			FCPPT_TEXT("error while reading ")
			+ _desc
			+ FCPPT_TEXT(" from file \"")
			+ filename_
			+ FCPPT_TEXT("\""));

	return swap_ ? fcppt::endianness::swap(ret) : ret;
}
