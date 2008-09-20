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


#ifndef SGE_VORBIS_FILE_HPP_INCLUDED
#define SGE_VORBIS_FILE_HPP_INCLUDED

#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>
#include <sge/path.hpp>
#include <sge/string.hpp>
#include <sge/audio/file.hpp>
#include <boost/noncopyable.hpp>
#include <vector>
#include <memory>
#include <cstdio>
#include <cstddef>

namespace sge
{
namespace vorbis
{

class file : public audio::file
{
	// TODO: ov_open_callbacks nutzen, damit std::ifstream geht und man auf FILE verzichten kann
	struct file_wrapper : boost::noncopyable
	{
		FILE *file_;

		file_wrapper() : file_(0) {}
		~file_wrapper() { if (file_) std::fclose(file_); }
	};

	// Ogg-Zeugs
	file_wrapper ogg_file_;
	OggVorbis_File ogg_stream_;

	audio::channel_type channels_;
	audio::sample_count sample_rate_;
	audio::sample_count bits_per_sample_;

	string ogg_error(long);
public:
	file(const path &, audio::sample_count);
	audio::sample_count read(audio::sample_count samples, audio::sample_container &);
	audio::sample_count read_all(audio::sample_container &);
	audio::channel_type channels() const;
	audio::sample_count sample_rate() const;
	audio::sample_count bits_per_sample() const;
	void reset();
};

}
}

#endif
