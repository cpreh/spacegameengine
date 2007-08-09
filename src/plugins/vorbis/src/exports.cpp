#include "../vorbis_loader.hpp"
#include "../../../plugin.hpp"

extern "C"
{

void plugin_version_info(sge::plugin_info* const p)
{
	if(!p)
		return;
	p->name = "vorbis loader plugin";
	p->description = "";
	p->plugin_version = 0x1;
	p->min_core_version = 0x1;
	p->type = sge::plugin_type::audio_loader;
}

sge::audio_loader* create_audio_loader()
{
	return new sge::vorbis_loader();
}

}
