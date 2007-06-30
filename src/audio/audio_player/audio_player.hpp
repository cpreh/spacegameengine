#ifndef SGE_PLAYER_HPP_INCLUDED
#define SGE_PLAYER_HPP_INCLUDED

// sge
#include "../../shared_ptr.hpp"
#include "../../plugin_traits.hpp"

// Own stuff
#include "../audio_loader/audio_file.hpp"

namespace sge
{
class sound;
struct audio_player
{
	virtual shared_ptr<sound> create_nonstream_sound(shared_ptr<audio_file>) = 0;
	virtual void update() = 0;
	virtual ~audio_player() {}
};

namespace detail
{

template<> struct plugin_traits<audio_player> {
	static const char* plugin_loader_name() { return "create_audio_player"; }
	static plugin_type get_plugin_type() { return PT_AudioPlayer; }
	typedef audio_player* (*loader_fun)();
};

}
}

#endif // PLAYER_HPP
