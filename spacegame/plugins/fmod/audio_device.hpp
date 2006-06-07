#ifndef SGE_FMOD_AUDIO_DEVICE_HPP_INCLUDED
#define SGE_FMOD_AUDIO_DEVICE_HPP_INCLUDED

#include "../../core/audio/audio_device.hpp"
#include "../../core/main/window.hpp"

namespace sge
{
	namespace fmod
	{
		class audio_device : public sge::audio_device {
		public:
			audio_device(unsigned num, window_ptr w);
			~audio_device();
			music_ptr load_music(const std::string& file);
		};
	}
}

#endif
