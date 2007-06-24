#include "../openal_player.hpp"
#include "../../../plugin.hpp"

extern "C"
{

void plugin_version_info(sge::plugin_info* const p)
{
	if(!p)
		return;
	p->name = "openal audio player plugin";
	p->description = "";
	p->plugin_version = 0x1;
	p->min_core_version = 0x1;
	p->type = sge::PT_AudioPlayer;
}

sge::audio_player* create_audio_player()
{
	return new sge::openal_player();
}

}
