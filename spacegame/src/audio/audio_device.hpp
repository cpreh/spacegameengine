#ifndef SGE_AUDIO_DEVICE_HPP_INCLUDED
#define SGE_AUDIO_DEVICE_HPP_INCLUDED

#include <string>
#include "../shared_ptr.hpp"
#include "./music.hpp"

namespace sge
{

class audio_device {
public:
	virtual ~audio_device(){}
	virtual music_ptr load_music(const std::string& name) = 0;
};

typedef shared_ptr<audio_device> audio_device_ptr;

}

#endif
