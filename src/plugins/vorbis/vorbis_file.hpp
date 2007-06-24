#ifndef SGE_VORBIS_FILE_HPP_INCLUDED
#define SGE_VORBIS_FILE_HPP_INCLUDED

// C
#include <cstdio>
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
	struct file_wrapper
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
