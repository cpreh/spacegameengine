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


#include "../file.hpp"
#include <sge/audio/exception.hpp>
#include <sge/log/headers.hpp>
#include <sge/endianness.hpp>
#include <sge/raw_vector_impl.hpp>
#include <sge/istream_util.hpp>
#include <sge/sstream.hpp>
#include <sge/format.hpp>
#include <sge/assert.hpp>
#include <boost/cstdint.hpp>

sge::wave::file::file(path const &filename)
: filename_(filename.string()),
  swap_(boost::logic::indeterminate),
  file_(filename_)
{
	if (!file_.is_open())
		throw audio::exception(
			SGE_TEXT("couldn't open wave file \"")+filename_+SGE_TEXT("\""));

	read_riff();
	read_wave();
}

sge::string const sge::wave::file::to_string() const
{
	sge::ostringstream ss;
	ss << "bits_per_sample: " << bits_per_sample() << ", "
	   << "sample_rate: " << sample_rate() << ", "
	   << "channels: " << channels() << ", "
	   << "samples: " << samples();
	return ss.str();
}

void sge::wave::file::reset()
{
	SGE_LOG_DEBUG(log::global(),log::_1 << "wave: resetting file");
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
			_array.size()+bytes_to_read));

	file_.read(
		reinterpret_cast<char*>(&_array[old_size]),
		bytes_to_read);

	if (bytes_per_sample() > static_cast<audio::sample_count>(1) && swap_)
		for (audio::sample_container::iterator i = _array.begin()+old_size; i != _array.end(); i += bytes_per_sample())
			swap_endianness(i,bytes_per_sample());

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
		extract_header(SGE_TEXT("riff"));

	// Endiankrams
	bool file_bigendian;

	if (rifftype == "RIFF")
		file_bigendian = false;
	else if (rifftype == "RIFX")
		file_bigendian = true;
	else
		throw audio::exception(SGE_TEXT("file \"")+filename_+SGE_TEXT("\" is not a riff file and thus not a wave file"));
	
	swap_ = file_bigendian == is_little_endian();

	// throw away riff size
	extract_primitive<boost::uint32_t>(SGE_TEXT("riff chunk size"));
}

void sge::wave::file::read_wave()
{
	if (extract_header(SGE_TEXT("wave")) != "WAVE")
		throw audio::exception(SGE_TEXT("the riff file \"")+filename_+SGE_TEXT("\" is not a wave file (wave header not present)"));

	ignore_chunks_until("fmt ");

	// ignore format chunk size
	extract_primitive<boost::uint32_t>(SGE_TEXT("format chunk size"));
		
	boost::uint16_t const audio_format = 
		extract_primitive<boost::uint16_t>(SGE_TEXT("audio format"));

	if (audio_format != static_cast<boost::uint16_t>(1))
		throw audio::exception(
			str(format(SGE_TEXT("wave file \"%1%\" is not pcm encoded (format code is %2%)")) 
				% filename_ % audio_format));

	channels_ = static_cast<audio::channel_type>(
			extract_primitive<boost::uint16_t>(SGE_TEXT("channel count")));

	sample_rate_ = static_cast<audio::sample_count>(
		extract_primitive<boost::uint32_t>(SGE_TEXT("sample rate")));

	// this is not needed with pcm encoding
	extract_primitive<boost::uint32_t>(SGE_TEXT("byte rate"));
	extract_primitive<boost::uint16_t>(SGE_TEXT("block alignment"));

	bits_per_sample_ = static_cast<audio::sample_count>(
		extract_primitive<boost::uint16_t>(SGE_TEXT("bits per sample")));
	
	ignore_chunks_until("data");

	boost::uint32_t const data_size = 
		extract_primitive<boost::uint32_t>(SGE_TEXT("data size"));
	
	samples_ = static_cast<audio::sample_count>(
		data_size / channels() / bytes_per_sample());
	
	samples_read_ = static_cast<audio::sample_count>(0);

	data_segment = file_.tellg();
}

void sge::wave::file::ignore_chunks_until(std::string const &desc)
{
	while (extract_header(SGE_TEXT("subchunk header")) != desc)
	{
		SGE_LOG_INFO(
			log::global(),
			log::_1 << SGE_TEXT("detected unknown subchunk in wave file \"")
			        << filename_
			        << SGE_TEXT("\""));

		file_.seekg(
			static_cast<std::streamoff>(
				extract_primitive<boost::uint32_t>(
					SGE_TEXT("subchunk size"))),
			std::ios_base::cur);
	}
}

std::string const sge::wave::file::extract_header(string const &_desc)
{
	raw_vector<char>::size_type const byte_count = 
		static_cast<raw_vector<char>::size_type>(4);
	raw_vector<char> bytes(byte_count);
	file_.read(&bytes[0],byte_count);
	if (file_.bad())
		throw audio::exception(
			SGE_TEXT("error while reading header \"")
			+ _desc
			+ SGE_TEXT("\" from file \"")
			+ filename_
			+ SGE_TEXT("\""));
	return std::string(bytes.begin(),bytes.end());
}

template<typename T>
T sge::wave::file::extract_primitive(string const &_desc)
{
	SGE_ASSERT(swap_ != boost::logic::indeterminate);

	T const ret = sge::read<T>(file_);

	if (file_.bad())
		throw audio::exception(
			SGE_TEXT("error while reading ")
			+ _desc
			+ SGE_TEXT(" from file \"")
			+ filename_
			+ SGE_TEXT("\""));

	return swap_ ? swap_endianness(ret) : ret;
}
