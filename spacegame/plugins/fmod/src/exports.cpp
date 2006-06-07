#include "../../../core/main/dllapi.hpp"
#include "../../../core/main/plugin.hpp"
#include "../audio_system.hpp"

extern "C"
{
	SGEDLLEXPORT void plugin_version_info(sge::plugin_info* const p)
	{
		if(!p)
			return;
		p->name = "fmod audio plugin";
		p->description = "";
		p->min_core_version = 0x1;
		p->plugin_version = 0x1;
		p->type = sge::PT_Audio;
	}

	SGEDLLEXPORT sge::audio_system* create_audio_system(const sge::window_ptr w)
	{
		return new sge::fmod::audio_system(w);
	}
}
