#ifndef SGE_AUDIO_SYSTEM_HPP_INCLUDED
#define SGE_AUDIO_SYSTEM_HPP_INCLUDED

#include <string>
#include <vector>
#include "../shared_ptr.hpp"
#include "../window.hpp"
#include "./audio_device.hpp"

namespace sge
{

struct driver_info {
	std::string name;
};

typedef std::vector<driver_info> driver_info_array;

class audio_system {
public:
	virtual ~audio_system(){}
	virtual void get_driver_info(driver_info_array& v) = 0;
	virtual audio_device_ptr create_audio_device(unsigned num = 0) = 0;
};

typedef shared_ptr<audio_system> audio_system_ptr;

}

#endif
