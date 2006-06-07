#include <stdexcept>
#include "../audio_system.hpp"
#include "../audio_device.hpp"
#include <fmod.h>

sge::fmod::audio_system::audio_system(const window_ptr w)
: w(w)
{
	if(FSOUND_SetOutput(-1) == false)
		throw std::runtime_error("FSOUND_SetOutput() failed");
}

sge::audio_device_ptr sge::fmod::audio_system::create_audio_device(const unsigned num)
{
	return audio_device_ptr(new audio_device(num,w));
}

void sge::fmod::audio_system::get_driver_info(driver_info_array& v)
{
	const int num = FSOUND_GetNumDrivers();
	v.reserve(num);
	for(int i = 0; i < num; ++i)
	{
		driver_info di;
		di.name = FSOUND_GetDriverName(i);
		v.push_back(di);
	}
}
