#ifndef SGE_FMOD_MUSIC_HPP_INCLUDED
#define SGE_FMOD_MUSIC_HPP_INCLUDED

#include "../../core/audio/music.hpp"
#include <fmod.h>

namespace sge
{
	namespace fmod
	{
		class music : public sge::music {
		public:
			music(const std::string& file);
			~music();
			void play(bool loop);
			void stop();
		private:
			FSOUND_STREAM* stream;
		};
	}
}

#endif
