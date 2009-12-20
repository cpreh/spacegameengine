/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <fcppt/text.hpp>
#include <sge/log/headers.hpp>
#include <sge/log/global.hpp>
#include <sge/endianness/is_little_endian.hpp>
#include <sge/container/raw_vector_impl.hpp>
#include <sge/assert.hpp>
#include <algorithm>
#include <iterator>

namespace
{
fcppt::string ogg_error(int const code)
{
	switch(code)
	{
		case OV_EREAD:
			return FCPPT_TEXT("a read from a media has returned an error");
		case OV_ENOTVORBIS:
			return FCPPT_TEXT("bitstream does not contain any vorbis data");
		case OV_EVERSION:
			return FCPPT_TEXT("vorbis version mismatch");
		case OV_EBADHEADER:
			return FCPPT_TEXT("invalid vorbis bitstream header");
		case OV_EFAULT:
			return FCPPT_TEXT("Internal logic fault (bug or heap/stack corruption)");
		case OV_ENOSEEK:
			return FCPPT_TEXT("bitstream is not seekable.");
		default:
			return FCPPT_TEXT("unknown ogg error");
	}
}
}

sge::vorbis::file::file(
	filesystem::path const &p)
:
	file_name(p.string()),
	stdstream(p, std::ios_base::binary)
{
	if (!stdstream.is_open())
		throw audio::exception(FCPPT_TEXT("vorbis: couldn't open file \"")+file_name+FCPPT_TEXT("\""));

	ov_callbacks callbacks;

	callbacks.read_func = &file::ogg_read_static;
	callbacks.seek_func = &file::ogg_seek_static;
	callbacks.close_func = &file::ogg_close_static;
	callbacks.tell_func = &file::ogg_tell_static;

	if (int error = ov_open_callbacks(this,&ogg_file,0,static_cast<long>(0),callbacks))
		throw audio::exception(FCPPT_TEXT("vorbis: error opening ogg vorbis file \"")+file_name+FCPPT_TEXT("\": ")+ogg_error(error));

	vorbis_info * const info = ov_info(&ogg_file,static_cast<int>(-1));
	if (!info)
		throw audio::exception(FCPPT_TEXT("vorbis: couldn't read file info from ogg vorbis file \"")+file_name+FCPPT_TEXT("\""));

	channels_ = static_cast<channel_type>(info->channels);
	sample_rate_ = static_cast<sample_count>(info->rate);
}

sge::audio::sample_count sge::vorbis::file::read(
	sample_count const samples,
	sample_container &data)
{
	/*
	if (stdstream.eof())
	{
		FCPPT_LOG_DEBUG(log::global(),log::_ << FCPPT_TEXT("vorbis: we're at the end, returning"));
		return static_cast<sample_count>(0);
	}
	*/

	sample_count const bytes_to_read = samples*channels()*bytes_per_sample();
	sample_container newdata(static_cast<sample_container::size_type>(bytes_to_read));

	sample_count bytes_read = static_cast<sample_count>(0);
	while (bytes_read < bytes_to_read)
	{
		int bitstream;

		long result = ov_read(
			&ogg_file,
			reinterpret_cast<char *>(&newdata[bytes_read]),
			static_cast<int>(bytes_to_read - bytes_read),
			static_cast<int>(!endianness::is_little_endian()),
			static_cast<int>(2), // 8 or 16 bit samples
			static_cast<int>(1), // 0 is unsigned data, 1 is signed
			&bitstream);

		switch (result)
		{
			case OV_HOLE:
				continue;
			case OV_EBADLINK:
				throw audio::exception(FCPPT_TEXT("vorbis: an invalid stream section was supplied to libvorbisfile, or the requested link is corrupt in file \"")+file_name+FCPPT_TEXT("\""));
			case OV_EINVAL:
				throw audio::exception(FCPPT_TEXT("vorbis: the initial file headers couldn't be read or are corrupt, or the initial open call for vf failed in file \"")+file_name+FCPPT_TEXT("\""));
		}

		if (result == static_cast<long>(0))
		{
			FCPPT_LOG_DEBUG(log::global(),log::_ << FCPPT_TEXT("vorbis: read until the end"));
			break;
		}

		bytes_read += static_cast<sample_count>(result);
	}

	std::copy(newdata.begin(),newdata.begin() + bytes_read,std::back_inserter(data));
	return bytes_read/bytes_per_sample();
}

sge::audio::sample_count sge::vorbis::file::read_all(
	sample_container &data)
{
	while (read(static_cast<sample_count>(16*4096),data))
		;
	return data.size()/bytes_per_sample();
}

sge::vorbis::file::channel_type
sge::vorbis::file::channels() const
{
	return channels_;
}

sge::vorbis::file::sample_count
sge::vorbis::file::sample_rate() const
{
	return sample_rate_;
}

sge::vorbis::file::sample_count
sge::vorbis::file::bits_per_sample() const
{
	return static_cast<sample_count>(16);
}

void sge::vorbis::file::reset()
{
	if (int error = ov_pcm_seek(&ogg_file,static_cast<ogg_int64_t>(0)))
		throw audio::exception(FCPPT_TEXT("vorbis: couldn't reset file \"")+file_name+FCPPT_TEXT("\": ")+ogg_error(error));
}

sge::vorbis::file::~file()
{
	int result = ov_clear(&ogg_file);
	SGE_ASSERT(!result);
}

std::size_t sge::vorbis::file::ogg_read_static(
	void * const ptr,
	std::size_t const size,
	std::size_t const nmemb,
	void * const datasource)
{
	return static_cast<sge::vorbis::file*>(datasource)->ogg_read(ptr,size,nmemb);
}

int sge::vorbis::file::ogg_seek_static(
	void * const datasource,
	ogg_int64_t const offset,
	int const whence)
{
	return static_cast<sge::vorbis::file*>(datasource)->ogg_seek(offset,whence);
}

int sge::vorbis::file::ogg_close_static(void *datasource)
{
	return static_cast<sge::vorbis::file*>(datasource)->ogg_close();
}

long sge::vorbis::file::ogg_tell_static(void *datasource)
{
	return static_cast<sge::vorbis::file*>(datasource)->ogg_tell();
}

std::size_t sge::vorbis::file::ogg_read(
	void * const ptr,
	std::size_t const size,  // size of a "package"
	std::size_t const nmemb) // how many packages to read
{
	if (stdstream.eof())
		return static_cast<std::size_t>(0);
	stdstream.read(static_cast<char *>(ptr),static_cast<std::streamsize>(size*nmemb));
	if (stdstream.bad())
		throw audio::exception(FCPPT_TEXT("vorbis: stream error while reading from file \"")+file_name+FCPPT_TEXT("\""));
	return static_cast<std::size_t>(stdstream.gcount()/size);
}

int sge::vorbis::file::ogg_seek(
	ogg_int64_t const offset,
	int whence)
{
	if (stdstream.eof())
		stdstream.clear();

	switch (whence)
	{
		case SEEK_SET:
			stdstream.seekg(static_cast<std::streamoff>(offset),std::ios_base::beg);
			if (stdstream.bad())
				throw audio::exception(FCPPT_TEXT("vorbis: stream error while reading from file \"")+file_name+FCPPT_TEXT("\""));
			break;
		case SEEK_CUR:
			stdstream.seekg(static_cast<std::streamoff>(offset),std::ios_base::cur);
			if (stdstream.bad())
				throw audio::exception(FCPPT_TEXT("vorbis: stream error while reading from file \"")+file_name+FCPPT_TEXT("\""));
			break;
		case SEEK_END:
			stdstream.seekg(static_cast<std::streamoff>(offset),std::ios_base::end);
			if (stdstream.bad())
				throw audio::exception(FCPPT_TEXT("vorbis: stream error while reading from file \"")+file_name+FCPPT_TEXT("\""));
			break;
		default:
			throw audio::exception(FCPPT_TEXT("vorbis: invalid seek parameter in file \"")+file_name+FCPPT_TEXT("\""));
	}
	return static_cast<int>(0);
}

int sge::vorbis::file::ogg_close()
{
	stdstream.close();
	// the return code is not checked, but zero indicates success in the orr library
	return static_cast<int>(0);
}

long sge::vorbis::file::ogg_tell()
{
	return static_cast<long>(stdstream.tellg());
}
