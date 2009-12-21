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


#ifndef SGE_VORBIS_FILE_HPP_INCLUDED
#define SGE_VORBIS_FILE_HPP_INCLUDED

#include <sge/audio/file.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/io/ifstream.hpp>
#include <fcppt/string.hpp>
#include <vorbis/vorbisfile.h>
#include <cstddef>

namespace sge
{
namespace vorbis
{
class file : public audio::file
{
public:
	typedef audio::sample_count sample_count;
	typedef audio::channel_type channel_type;
	typedef audio::sample_container sample_container;

	explicit file(
		fcppt::filesystem::path const &
	);
	sample_count read(sample_count samples, sample_container &);
	sample_count read_all(sample_container &);

	channel_type channels() const;
	sample_count sample_rate() const;
	sample_count bits_per_sample() const;
	void reset();

	~file();

private:
	fcppt::string const         file_name;
	fcppt::io::ifstream         stdstream;
	OggVorbis_File              ogg_file;
	channel_type                channels_;
	sample_count                sample_rate_;

	// ogg callbacks
	static std::size_t ogg_read_static(void *ptr, std::size_t size, std::size_t nmemb, void *datasource);
	static int ogg_seek_static(void *datasource, ogg_int64_t offset, int whence);
	static int ogg_close_static(void *datasource);
	static long ogg_tell_static(void *datasource);

	std::size_t ogg_read(void *ptr, std::size_t size, std::size_t nmemb);
	int ogg_seek(ogg_int64_t offset, int whence);
	int ogg_close();
	long ogg_tell();
};
}
}

#endif
