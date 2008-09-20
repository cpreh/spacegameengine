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
#include <sge/audio/exception.hpp>
#include <sge/raw_vector_impl.hpp>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstddef>
#include <cstring>
#include <cerrno>
#include <cassert>


sge::vorbis::file::file(
	const path &_filename,
	const audio::sample_count _bits_per_sample)
: bits_per_sample_(_bits_per_sample)
{
	assert(bits_per_sample_ == 8 || bits_per_sample_ == 16);

	if((ogg_file_.file_ = std::fopen(iconv(_filename.string()).c_str(), "rb")) == 0)
		throw audio::exception(SGE_TEXT("Couldn't open ogg file \"") + _filename.string() + SGE_TEXT("\": ") + iconv(std::string(std::strerror(errno))));
 
 	// File pointer, ogg structure pointer, Mist, Mist
	int result;
	vorbis_info *vorbis_info;
	if((result = ov_open(ogg_file_.file_, &ogg_stream_, 0, 0)) < 0)
		throw audio::exception(SGE_TEXT("Invalid ogg file: ") + ogg_error(result));

	if ((vorbis_info = ov_info(&ogg_stream_, -1)) == 0)
		throw audio::exception(SGE_TEXT("Error getting ogg file info: ") + ogg_error(result));

	channels_ = vorbis_info->channels;
	sample_rate_ = vorbis_info->rate;
}

sge::audio::sample_count
sge::vorbis::file::read(
	const audio::sample_count _sample_count,
	audio::sample_container &_data)
{
	audio::sample_count bytes_to_read = _sample_count * channels() * 2;
	_data.resize_uninitialized(bytes_to_read);

	audio::sample_count bytes_read = 0;
	while (bytes_read < bytes_to_read)
	{
		int bitstream;
		long result = ov_read(
			&ogg_stream_,
			reinterpret_cast<char *>(_data.data()) + bytes_read,
			static_cast<int>(bytes_to_read - bytes_read),
			0,
			(bits_per_sample_ == 8) ? 1 : 2, 1, &bitstream);
		if (result < 0)
			throw audio::exception(SGE_TEXT("Error reading ogg file: ") + ogg_error(result));

		// EOF?
		if (result == 0)
			break;

		bytes_read += result;
	}

	return bytes_read;
}

sge::audio::sample_count
sge::vorbis::file::read_all(
	audio::sample_container &_data)
{
	// Wir wissen nicht, wie viele Samples wir kriegen, also lesen wir in diskreten Bloecken und fuegen die in _data ein.
	// TODO: Das hier vielleicht optimieren.
	const int buffer_size = 4096; unsigned char buffer[buffer_size];
	while (true)
	{
		int bitstream;
		long result = ov_read(&ogg_stream_, reinterpret_cast<char *>(buffer), buffer_size, 0, (bits_per_sample_ == 8) ? 1 : 2, 1, &bitstream);
		if (result < 0)
			throw audio::exception(SGE_TEXT("Error reading ogg file: ") + ogg_error(result));

		// EOF?
		if (result == 0)
			break;

		std::copy(buffer,buffer + result,std::back_inserter(_data));
	}
	return _data.size();
}

void sge::vorbis::file::reset()
{
	// Hier seeken wir einfach zu Zeit 0
	int result = ov_time_seek(&ogg_stream_,0.0);
	if (result != 0)
		throw audio::exception(SGE_TEXT("Error resetting ogg stream: ") + ogg_error(result));
}

sge::string sge::vorbis::file::ogg_error(const long code)
{
	switch(code)
	{
		case OV_EREAD:
			return SGE_TEXT("Read from media");
		case OV_ENOTVORBIS:
			return SGE_TEXT("Not Vorbis data");
		case OV_EVERSION:
			return SGE_TEXT("Vorbis version mismatch");
		case OV_EBADHEADER:
			return SGE_TEXT("Invalid Vorbis header");
		case OV_EFAULT:
			return SGE_TEXT("Internal logic fault (bug or heap/stack corruption)");
		case OV_ENOSEEK:
			return SGE_TEXT("Bitstream is not seekable.");
		default:
			return SGE_TEXT("Unknown Ogg error");
	}
}

sge::audio::channel_type sge::vorbis::file::channels() const
{
	return channels_;
}

sge::audio::sample_count sge::vorbis::file::sample_rate() const
{
	return sample_rate_;
}

sge::audio::sample_count sge::vorbis::file::bits_per_sample() const
{
	return bits_per_sample_;
}
