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
#include <sge/iconv.hpp>
#include <sge/endianness.hpp>
#include <sge/raw_vector_impl.hpp>
#include <sge/istream_util.hpp>
#include <sge/audio/exception.hpp>
#include <algorithm>
#include <string>
#include <sstream>
#include <boost/cstdint.hpp>
#include <cstddef>
#include <cassert>
#include <climits>

sge::wave::file::file(const path &filename)
: filename_(filename),
  swap_(boost::logic::indeterminate),
  loaded_(false)
{
	load();
}

const std::string sge::wave::file::to_string() const
{
	std::ostringstream ss;
	ss << "bits_per_sample: " << bits_per_sample_ << ", "
	   << "sample_rate: " << sample_rate_ << ", "
	   << "channels: " << channels_ << ", "
	   << "samples: " << samples_;
	return ss.str();
}

void sge::wave::file::load()
{
	assert(!loaded_);

	// TODO: use filesystem streams
	file_.open(iconv(filename_.string()).c_str());

	if (!file_.is_open())
		throw audio::exception(SGE_TEXT("Couldn't open file \"") + filename_.string() + SGE_TEXT("\""));

	read_riff();
	read_wave();
	read_data();

	loaded_ = true;
}

void sge::wave::file::read_riff()
{
	const std::string rifftype = extract_string(4,"riff header");

	// Endiankrams
	bool file_bigendian;

	if (rifftype == "RIFF")
		file_bigendian = false;
	else if (rifftype == "RIFX")
		file_bigendian = true;
	else
		throw audio::exception(SGE_TEXT("Not a valid riff file!"));
	
	swap_ = file_bigendian == is_little_endian();

	// Groesse des Wave-Teils der Datei
	// TODO: Checken ob man das wirklich braucht und sonst ueberspringen.
	//boost::int32_t chunksize = extract_primitive<boost::int32_t>("chunk size") - 36;
}

void sge::wave::file::read_wave()
{
	if (extract_string(8,"wave header") != "WAVEfmt ")
		throw audio::exception(SGE_TEXT("Not a valid wave file!"));
	if (extract_primitive<boost::uint32_t>("subchunksize") != 16)
		throw audio::exception(SGE_TEXT("File is not PCM!"));
	if (extract_primitive<boost::uint16_t>("audio format") != 1)
		throw audio::exception(SGE_TEXT("File is not linear quantisized!"));
	channels_ = extract_primitive<boost::uint16_t>("channel count");
	sample_rate_ = extract_primitive<boost::uint32_t>("sample rate");
	extract_primitive<boost::uint32_t>("byte rate");
	extract_primitive<boost::uint16_t>("block alignment");
	bits_per_sample_ = extract_primitive<boost::uint16_t>("bits per sample");
}

void sge::wave::file::read_data()
{
	if (extract_string(4,"data header") != "data")
		throw audio::exception(SGE_TEXT("File is not a valid wave file!"));
	
	//buffer_size_ = extract_primitive<boost::uint32_t>("data size");
	samples_ = extract_primitive<boost::uint32_t>("data size") / channels_ / (bits_per_sample_/8);
	samples_read_ = 0;
}

const std::string sge::wave::file::extract_string(const std::size_t _bytes, const std::string &_desc)
{
	assert(_bytes < 32);

	char array[32];
	file_.read(array,_bytes);
	if (file_.eof() || !file_)
		throw audio::exception(SGE_TEXT("Unexpected end of file or error while reading ") + iconv(_desc) + SGE_TEXT("!"));

	array[_bytes] = 0;
	return std::string(array);
}

template<typename T>
T sge::wave::file::extract_primitive(const std::string &_desc)
{
//	assert(swap_ != boost::logic::indeterminate);

	T const ret = sge::read<T>(file_);
	if (file_.eof() || !file_)
		throw audio::exception(
			SGE_TEXT("Unexpected end of file or error while reading ") + iconv(_desc) + SGE_TEXT("!"));

	return swap_ ? swap_endianness(ret) : ret;
}

sge::audio::sample_count sge::wave::file::read(const audio::sample_count _sample_count, audio::sample_container &_array) 
{
	assert(_array.size() == 0);

	const audio::sample_count samples_to_read = std::min(_sample_count,samples_ - samples_read_);
	if (samples_to_read == 0)
		return 0;

	audio::sample_count bytes_to_read = samples_to_read * channels_ * (bits_per_sample_/8);
	_array.resize_uninitialized(bytes_to_read);
	file_.read(reinterpret_cast<char *>(_array.data()),bytes_to_read);

	if (swap_ && bits_per_sample_ > 8)
		for (audio::sample_count i = 0; i < bytes_to_read; i += (bits_per_sample_/8))
			swap_endianness(&_array[i],bits_per_sample_/8);

	samples_read_ += samples_to_read;
	return samples_to_read;
}

void sge::wave::file::reset()
{
	assert(loaded_);

	// Dateipointer resetten
	file_.seekg(-static_cast<std::streamsize>(samples_) * (bits_per_sample_/8) * channels_,std::ios_base::end);
	samples_read_ = 0;
}

sge::audio::sample_count sge::wave::file::read_all(audio::sample_container &_array) 
{ 
	assert(_array.size() == 0);

	return read(samples_ - samples_read_,_array);
}

sge::audio::sample_count sge::wave::file::bits_per_sample() const
{
	assert(loaded_);
	return bits_per_sample_;
}
	
sge::audio::sample_count sge::wave::file::sample_rate() const
{
	assert(loaded_);
	return sample_rate_;
}

sge::audio::channel_type sge::wave::file::channels() const
{
	assert(loaded_);
	return channels_;
}

sge::audio::sample_count sge::wave::file::samples() const
{
	assert(loaded_);
	return samples_;
}
