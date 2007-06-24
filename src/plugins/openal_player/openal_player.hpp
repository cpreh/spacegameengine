#ifndef SGE_OPENAL_PLAYER_INCLUDED
#define SGE_OPENAL_PLAYER_INCLUDED

// C++
#include <list>
// Own stuff
#include "../../audio/audio_player/audio_player.hpp"

namespace sge
{
class openal_player : public audio_player
{
	void check(const std::string &);
	std::list<sound *> sounds;

	public:
		openal_player();

		void register_sound(sound *p) { sounds.push_back(p); } 
		void unregister_sound(sound *p) { sounds.remove(p); }
		
		shared_ptr<sound> create_nonstream_sound(shared_ptr<audio_file> _audio_file);
		shared_ptr<sound> create_stream_sound(shared_ptr<audio_file> _audio_file);
		void update();
};
}

#endif 
