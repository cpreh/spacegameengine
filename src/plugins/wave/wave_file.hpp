#ifndef WAVE_FILE_HPP
#define WAVE_FILE_HPP

// C
#include <cassert>
#include <fstream>
// C++
#include <sstream>
#include <vector>
#include <string>
#include <stdexcept>
// Boost
#include <boost/logic/tribool.hpp>
// sge
#include "../../endianness.hpp"
// Own stuff
#include "../../audio/audio_loader/audio_file.hpp"
#include "../../audio/audio_exception.hpp"

namespace sge
{
class wave_file : public audio_file 
{
	const std::string          filename_;
	// Ob die Bytes geswappt werden muessen
	boost::logic::tribool      swap_;
	std::ifstream              file_;
	std::size_t                samples_,samples_read_;
	std::vector<unsigned char> buffer_;

	// Ob das Ding geladen wurde
	bool                       loaded_;

	// "Pflichtfelder"
	int                        channels_;
	int                        sample_rate_;
	int                        bits_per_sample_;

	// Interne Funktionen
	void read_riff();
	void read_wave();
	void read_data();
	void load();

	std::string extract_string(std::size_t _bytes,const std::string &_desc)
	{
		assert(_bytes < 32);

		char array[32];
		file_.read(array,_bytes);
		if (file_.eof() || !file_)
			throw audio_exception("Unexpected end of file or error while reading "+_desc+"!");

		array[_bytes] = 0;
		return std::string(array);
	}

	template<typename T>
	T extract_primitive(const std::string &_desc)
	{
		assert(swap_ == true || swap_ == false);
		assert(sizeof(T) < 64);

		char array[64];
		file_.read(array,sizeof(T));
		if (file_.eof() || !file_)
			throw audio_exception("Unexpected end of file or error while reading "+_desc+"!");
		T v = *reinterpret_cast<T *>(array);
		return swap_ ? swap_endianness(v) : v;
	}

	public:
	wave_file(const std::string &);

	std::string to_string() const
	{
		std::ostringstream ss;
		ss << "bits_per_sample: " << bits_per_sample_ << ", "
		   << "sample_rate: " << sample_rate_ << ", "
			 << "channels: " << channels_ << ", "
			 << "samples: " << samples_;
		return ss.str();
	}

	int bits_per_sample() const { assert(loaded_); return bits_per_sample_; }
	int sample_rate() const { assert(loaded_); return sample_rate_; }
	int channels() const { assert(loaded_); return channels_; }
	int samples() const { assert(loaded_); return samples_; }
	void reset();

	std::size_t read(std::size_t,std::vector<unsigned char> &);
	std::size_t read_all(std::vector<unsigned char> &);
};
}

#endif // WAVE_FILE_HPP
