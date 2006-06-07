#include "../../../core/main/dllapi.hpp"
#include "../../../core/main/plugin.hpp"
#include "../image_loader.hpp"

extern "C"
{
	SGEDLLEXPORT void plugin_version_info(sge::plugin_info* const p)
	{
		if(!p)
			return;
		p->name = "devil image loader plugin";
		p->description = "";
		p->plugin_version = 0x1;
		p->min_core_version = 0x1;
		p->type = sge::PT_ImageLoader;
	}
	
	SGEDLLEXPORT sge::image_loader* create_image_loader()
	{
		return new sge::devil::image_loader();
	}
}
