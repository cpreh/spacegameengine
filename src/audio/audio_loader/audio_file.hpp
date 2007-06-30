#ifndef SGE_AUDIO_FILE_HPP_INCLUDED
#define SGE_AUDIO_FILE_HPP_INCLUDED

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
	virtual ~audio_file() {}
};
}

#endif // AUDIO_FILE_HPP
