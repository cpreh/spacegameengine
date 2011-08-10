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
#include <sge/audio/unsupported_format.hpp>
#include <sge/audio/file_exception.hpp>
#include <sge/log/global.hpp>
#include <fcppt/endianness/is_little_endian.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/io/cifstream.hpp>
#include <fcppt/text.hpp>
#include <fcppt/move.hpp>
#include <fcppt/sn_cast.hpp>
#include <fcppt/assert.hpp>
#include <algorithm>
#include <iterator>

namespace
{
fcppt::string
ogg_error(
	int const code)
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
	stream_ptr _stdstream,
	sge::audio::optional_path const &_file_name)
:
	file_name_(
		_file_name),
	stdstream_(
		fcppt::move(
			_stdstream))
{
	ov_callbacks callbacks;

	callbacks.read_func = &file::ogg_read_static;
	callbacks.seek_func = &file::ogg_seek_static;
	callbacks.close_func = &file::ogg_close_static;
	callbacks.tell_func = &file::ogg_tell_static;

	// This might fail with ENOTVORBIS, so we send an unsupported_format
	// here (but technically, it could be a different error. FIXME: Do
	// better error reporting here.
	if(int error = ov_open_callbacks(this,&ogg_file_,0,static_cast<long>(0),callbacks))
		throw audio::unsupported_format(
			file_name_,
			ogg_error(
				error));

	vorbis_info * const info =
		ov_info(
			&ogg_file_,
			-1);

	if (!info)
		throw audio::file_exception(
			file_name_,
			FCPPT_TEXT("couldn't read file info from ogg vorbis file"));

	channels_ =
		fcppt::sn_cast<channel_type>(
			info->channels);
	sample_rate_ =
		fcppt::sn_cast<sample_count>(
			info->rate);

	//std::cerr << "channels: " << channels_ << ", bits per sample: " << bits_per_sample() << ", sampling rate: " << info->rate << "\n";
	//std::cerr << "bitrate: upper: " << info->bitrate_upper << ", nominal: " << info->bitrate_nominal << ", lower: " << info->bitrate_lower << "\n";
}


sge::audio::sample_count
sge::vorbis::file::read(
	sample_count const samples,
	sample_container &data)
{
	// The EOF test is stupid because the ogg library could have already
	// read all the file's bytes while determining the sample rate (and
	// stuff), so we don't have to test this. But I leave it here in
	// case any problems arise.
	/*
	if (stdstream_->eof())
	{
		FCPPT_LOG_DEBUG(log::global(),fcppt::log::_ << FCPPT_TEXT("vorbis: we're at the end, returning"));
		return 0;
	}
	*/

	sample_count const bytes_to_read =
		samples*
		channels()*
		bytes_per_sample();

	sample_container newdata(
		fcppt::sn_cast<sample_container::size_type>(
			bytes_to_read));

	sample_count bytes_read =
		0;

	// When reading from the file, you might encounter a bad fragment
	// which is indicated by OV_HOLE. According to a mailing list post,
	// we can just ignore holes.
	bool hit_a_hole =
		true;
	while(hit_a_hole)
	{
		int bitstream;

		long result =
			ov_read(
				&ogg_file_,
				reinterpret_cast<char *>(
					&newdata[bytes_read]),
				static_cast<int>(
					bytes_to_read - bytes_read),
				static_cast<int>(
					!fcppt::endianness::is_little_endian()),
				2, // 8 or 16 bit samples
				1, // 0 is unsigned data, 1 is signed
				&bitstream);

		switch (result)
		{
			case OV_HOLE:
				hit_a_hole = true;
				FCPPT_LOG_WARNING(
					log::global(),
					fcppt::log::_
						<< FCPPT_TEXT("Encountered corrupt vorbis data")
						<<
							(file_name_
							?
								(FCPPT_TEXT(" in file ")+(fcppt::filesystem::path_to_string(*file_name_)))
							:
								fcppt::string()));
			case OV_EBADLINK:
				throw audio::file_exception(
					file_name_,
					FCPPT_TEXT("an invalid stream section was supplied to libvorbisfile, or the requested link is corrupt"));
			case OV_EINVAL:
				throw audio::file_exception(
					file_name_,
					FCPPT_TEXT("the initial file headers couldn't be read or are corrupt, or the initial open call for vf failed"));
		}

		hit_a_hole = false;

		if(result == 0)
		{
			FCPPT_LOG_DEBUG(
				log::global(),
				fcppt::log::_ << FCPPT_TEXT("vorbis: read until the end"));
		}

		bytes_read =
			static_cast<sample_count>(
				bytes_read + static_cast<unsigned long>(result));
	}

	std::copy(
		newdata.begin(),
		newdata.begin() + bytes_read,
		std::back_inserter(
			data));

	FCPPT_ASSERT(
		bytes_read % bytes_per_sample() == 0);

//	std::cout << "got " << (bytes_read/bytes_per_sample()) << " samples, sample rate is " << sample_rate() << "\n";

	return bytes_read/bytes_per_sample();
}

sge::audio::sample_count
sge::vorbis::file::read_all(
	sample_container &data)
{
	while (read(fcppt::sn_cast<sample_count>(16*4096),data))
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

sge::audio::sample_count
sge::vorbis::file::expected_package_size() const
{
	// FIXME: How do we determine the correct size? :(
	return 2048;
}

void sge::vorbis::file::reset()
{
	if (int error = ov_pcm_seek(&ogg_file_,0))
		throw audio::file_exception(
			file_name_,
			FCPPT_TEXT("vorbis: couldn't reset file: ")+
			ogg_error(
				error));
}

sge::vorbis::file::~file()
{
	int result =
		ov_clear(
			&ogg_file_);
	FCPPT_ASSERT(
		!result);
}

std::size_t
sge::vorbis::file::ogg_read_static(
	void * const ptr,
	std::size_t const size,
	std::size_t const nmemb,
	void * const datasource)
{
	return
		static_cast<sge::vorbis::file*>(datasource)->ogg_read(
			ptr,
			size,
			nmemb);
}

int
sge::vorbis::file::ogg_seek_static(
	void * const datasource,
	ogg_int64_t const offset,
	int const whence)
{
	return
		static_cast<sge::vorbis::file*>(datasource)->ogg_seek(
			offset,
			whence);
}

int
sge::vorbis::file::ogg_close_static(void *datasource)
{
	return
		static_cast<sge::vorbis::file*>(
			datasource)->ogg_close();
}

long
sge::vorbis::file::ogg_tell_static(void *datasource)
{
	return
		static_cast<sge::vorbis::file*>(datasource)->ogg_tell();
}

std::size_t
sge::vorbis::file::ogg_read(
	void * const ptr,
	std::size_t const size,  // size of a "package"
	std::size_t const nmemb) // how many packages to read
{
	if(stdstream_->eof())
		return 0;
	stdstream_->read(
		static_cast<char *>(
			ptr),
		static_cast<std::streamsize>(
			size*nmemb));
	if(stdstream_->bad())
		throw audio::file_exception(
			file_name_,
			FCPPT_TEXT("vorbis: stream error"));
	return
		static_cast<std::size_t>(stdstream_->gcount()/size);
}

int
sge::vorbis::file::ogg_seek(
	ogg_int64_t const offset,
	int whence)
{
	if(stdstream_->eof())
		stdstream_->clear();

	switch (whence)
	{
		case SEEK_SET:
			stdstream_->seekg(
				fcppt::sn_cast<std::streamoff>(
					offset),
				std::ios_base::beg);

			if (stdstream_->bad())
				throw audio::file_exception(
					file_name_,
					FCPPT_TEXT("vorbis: stream error"));
			break;
		case SEEK_CUR:
			stdstream_->seekg(
				fcppt::sn_cast<std::streamoff>(
					offset),
				std::ios_base::cur);
			if (stdstream_->bad())
				throw audio::file_exception(
					file_name_,
					FCPPT_TEXT("vorbis: stream error"));
			break;
		case SEEK_END:
			stdstream_->seekg(
				fcppt::sn_cast<std::streamoff>(
					offset),
				std::ios_base::end);
			if (stdstream_->bad())
				throw audio::file_exception(
					file_name_,
					FCPPT_TEXT("vorbis: stream error"));
			break;
		default:
			throw audio::file_exception(
				file_name_,
				FCPPT_TEXT("vorbis: invalid seek parameter"));
	}
	return 0;
}

int
sge::vorbis::file::ogg_close()
{
	// Kind of a hack here, sorry.
	if (file_name_)
		static_cast<fcppt::io::cifstream &>(
			*stdstream_).close();
	// the return code is not checked, but zero indicates success in the orr library
	return 0;
}

long
sge::vorbis::file::ogg_tell()
{
	return
		// Doesn't work (investigate?)
		//fcppt::sn_cast<long>(
		static_cast<long>(
			stdstream_->tellg());
}
