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

// C
#include <cstdio>
#include <cstddef>
// C++
#include <vector>
#include <memory>
#include <string>
// boost
#include <boost/noncopyable.hpp>
// ogg/vorbis stuff
#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>
// Own stuff
#include "../../audio/audio_loader/audio_file.hpp"

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

	int channels_;
	int sample_rate_;
	int bits_per_sample_;

	std::string ogg_error(int);
	public:
	vorbis_file(const std::string &,int);
	std::size_t read(std::size_t sample_count,std::vector<unsigned char> &);
	std::size_t read_all(std::vector<unsigned char> &);
	int channels() const { return channels_; }
	int sample_rate() const { return sample_rate_; }
	int bits_per_sample() const { return bits_per_sample_; }
	void reset();
};
}

#endif
