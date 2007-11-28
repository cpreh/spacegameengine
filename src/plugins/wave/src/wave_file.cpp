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


// C
#include <cstddef>
#include <cassert>
// C++
#include <algorithm>
#include <string>
// Boost
#include <boost/cstdint.hpp>
// Own stuff
#include "../wave_file.hpp"

sge::wave_file::wave_file(const std::string &filename) : filename_(filename),swap_(boost::logic::indeterminate),loaded_(false)
{
	load();
}

void sge::wave_file::load()
{
	assert(!loaded_);

	file_.open(filename_.c_str());

	if (!file_.is_open())
		throw audio_exception("Couldn't open file \""+filename_+"\"");

	read_riff();
	read_wave();
	read_data();

	loaded_ = true;
}

void sge::wave_file::read_riff()
{
	const std::string rifftype = extract_string(4,"riff header");

	// Endiankrams
	bool file_bigendian;

	if (rifftype == "RIFF")
		file_bigendian = false;
	else if (rifftype == "RIFX")
		file_bigendian = true;
	else
		throw audio_exception("Not a valid riff file!");
	
	swap_ = file_bigendian == is_little_endian();

	// Groesse des Wave-Teils der Datei
	// TODO: Checken ob man das wirklich braucht und sonst ueberspringen.
	boost::int32_t chunksize = extract_primitive<boost::int32_t>("chunk size") - 36;
}

void sge::wave_file::read_wave()
{
	if (extract_string(8,"wave header") != "WAVEfmt ")
		throw audio_exception("Not a valid wave file!");
	if (extract_primitive<boost::uint32_t>("subchunksize") != 16)
		throw audio_exception("File is not PCM!");
	if (extract_primitive<boost::uint16_t>("audio format") != 1)
		throw audio_exception("File is not linear quantisized!");
	channels_ = extract_primitive<boost::uint16_t>("channel count");
	sample_rate_ = extract_primitive<boost::uint32_t>("sample rate");
	extract_primitive<boost::uint32_t>("byte rate");
	extract_primitive<boost::uint16_t>("block alignment");
	bits_per_sample_ = extract_primitive<boost::uint16_t>("bits per sample");
}

void sge::wave_file::read_data()
{
	if (extract_string(4,"data header") != "data")
		throw audio_exception("File is not a valid wave file!");
	
	//buffer_size_ = extract_primitive<boost::uint32_t>("data size");
	samples_ = extract_primitive<boost::uint32_t>("data size") / channels_ / (bits_per_sample_/8);
	samples_read_ = 0;
}

std::size_t sge::wave_file::read(std::size_t _sample_count,std::vector<unsigned char> &_array) 
{
	assert(_array.size() == 0);

	std::size_t samples_to_read = std::min(_sample_count,samples_ - samples_read_);
	if (samples_to_read == 0)
		return 0;

	std::size_t bytes_to_read = samples_to_read * channels_ * (bits_per_sample_/8);
	_array.resize(bytes_to_read);
	file_.read(reinterpret_cast<char *>(&_array[0]),bytes_to_read);

	if (swap_ && bits_per_sample_ > 8)
		for (std::size_t i = 0; i < bytes_to_read; i += (bits_per_sample_/8))
			swap_endianness(&_array[i],bits_per_sample_/8);

	samples_read_ += samples_to_read;
	return samples_to_read;
}

void sge::wave_file::reset()
{
	assert(loaded_);

	// Dateipointer resetten
	file_.seekg(-static_cast<std::streamsize>(samples_) * (bits_per_sample_/8) * channels_,std::ios_base::end);
	samples_read_ = 0;
}

std::size_t sge::wave_file::read_all(std::vector<unsigned char> &_array) 
{ 
	assert(_array.size() == 0);

	return read(samples_ - samples_read_,_array);
}
