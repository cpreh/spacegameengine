#ifndef AUDIO_FILE_HPP
#define AUDIO_FILE_HPP

// C++
#include <vector>

namespace sge
{
class audio_file
{
	public:
	virtual std::size_t read(std::size_t sample_count,std::vector<unsigned char> &) = 0;
	virtual std::size_t read_all(std::vector<unsigned char> &) = 0;
	virtual int channels() const = 0;
	virtual int sample_rate() const = 0;
	virtual int bits_per_sample() const = 0;
	virtual void reset() = 0;
};
}

#endif // AUDIO_FILE_HPP
