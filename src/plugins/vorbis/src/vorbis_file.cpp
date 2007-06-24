// C
#include <cstring>
#include <cerrno>
#include <cassert>
// C++
#include <algorithm>
// Own stuff
#include "../vorbis_file.hpp"
#include "../../../audio/audio_exception.hpp"

sge::vorbis_file::vorbis_file(const std::string &_filename,int _bits_per_sample)
{
	assert(_bits_per_sample == 8 || _bits_per_sample == 16);

	if((ogg_file_.file_ = std::fopen(_filename.c_str(), "rb")) == 0)
		throw audio_exception("Couldn't open ogg file \""+_filename+"\": "+std::string(std::strerror(errno)));
 
 	// File pointer, ogg structure pointer, Mist, Mist
	int result;
	vorbis_info *vorbis_info;
	if((result = ov_open(ogg_file_.file_, &ogg_stream_, 0, 0)) < 0)
		throw audio_exception("Invalid ogg file: "+ogg_error(result));

	if ((vorbis_info = ov_info(&ogg_stream_, -1)) == 0)
		throw audio_exception("Error getting ogg file info: "+ogg_error(result));

	channels_ = vorbis_info->channels;
	sample_rate_ = vorbis_info->rate;
	bits_per_sample_ = _bits_per_sample;
}

std::size_t sge::vorbis_file::read(std::size_t _sample_count,std::vector<unsigned char> &_data)
{
	std::size_t bytes_to_read = _sample_count * channels_ * 2;
	_data.resize(bytes_to_read);

	long bytes_read = 0;
	while (bytes_read < bytes_to_read)
	{
		int bitstream;
		long result = ov_read(&ogg_stream_, reinterpret_cast<char *>(&_data[0]) + bytes_read, bytes_to_read - bytes_read, 0, (bits_per_sample_ == 8) ? 1 : 2, 1, &bitstream);
		if (result < 0)
			throw audio_exception("Error reading ogg file: "+ogg_error(result));

		// EOF?
		if (result == 0)
			break;

		bytes_read += result;
	}

	return bytes_read;
}

std::size_t sge::vorbis_file::read_all(std::vector<unsigned char> &_data)
{
	// Wir wissen nicht, wie viele Samples wir kriegen, also lesen wir in diskreten Bloecken und fuegen die in _data ein.
	// TODO: Das hier vielleicht optimieren.
	const int buffer_size = 4096; unsigned char buffer[buffer_size];
	while (true)
	{
		int bitstream;
		long result = ov_read(&ogg_stream_, reinterpret_cast<char *>(buffer), buffer_size, 0, (bits_per_sample_ == 8) ? 1 : 2, 1, &bitstream);
		if (result < 0)
			throw audio_exception("Error reading ogg file: "+ogg_error(result));

		// EOF?
		if (result == 0)
			break;

		std::copy(buffer,buffer + result,std::back_inserter(_data));
	}
	return _data.size();
}

void sge::vorbis_file::reset()
{
	// Hier seeken wir einfach zu Zeit 0
	int result = ov_time_seek(&ogg_stream_,0.0);
	if (result != 0)
		throw audio_exception("Error resetting ogg stream: "+ogg_error(result));
}

std::string sge::vorbis_file::ogg_error(int code)
{
	switch(code)
	{
		case OV_EREAD:
			return "Read from media";
		case OV_ENOTVORBIS:
			return "Not Vorbis data";
		case OV_EVERSION:
			return "Vorbis version mismatch";
		case OV_EBADHEADER:
			return "Invalid Vorbis header";
		case OV_EFAULT:
			return "Internal logic fault (bug or heap/stack corruption)";
		case OV_ENOSEEK:
			return "Bitstream is not seekable.";
		default:
			return "Unknown Ogg error";
	}
	return "This shouldn't happen!";
}
