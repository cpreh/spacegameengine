#ifndef SGE_FMOD_AUDIO_SYSTEM_HPP_INCLUDED
#define SGE_FMOD_AUDIO_SYSTEM_HPP_INCLUDED

#include "../../core/audio/audio_system.hpp"

namespace sge
{
	namespace fmod
	{
		class audio_system : public sge::audio_system {
		public:
			audio_system(window_ptr w);
			void get_driver_info(driver_info_array& v);
			audio_device_ptr create_audio_device(unsigned num);
		private:
			window_ptr w;
		};
	}
}

#endif
