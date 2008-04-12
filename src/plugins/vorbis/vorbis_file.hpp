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
#include <sge/audio/loader/audio_file.hpp>
#include <boost/noncopyable.hpp>
#include <vector>
#include <memory>
#include <cstdio>
#include <cstddef>

namespace sge
{
class vorbis_file : public audio_file
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

	channel_type channels_;
	sample_type sample_rate_;
	sample_type bits_per_sample_;

	string ogg_error(long);
	public:
	vorbis_file(const path &, sample_type);
	sample_type read(sample_type samples, raw_array_type &);
	sample_type read_all(raw_array_type &);
	channel_type channels() const;
	sample_type sample_rate() const;
	sample_type bits_per_sample() const;
	void reset();
};
}

#endif
