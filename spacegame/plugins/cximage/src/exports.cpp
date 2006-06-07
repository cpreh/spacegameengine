#include "../../../core/main/dllapi.hpp"
#include "../../../core/main/plugin_manager.hpp"
#include "../pic_loader.hpp"

extern "C"
{
	DLLEXPORT void dll_version_info(sge::plugin_info* p)
	{
		if(!p)
			return;
		p->name = "cxImage pic loader plugin";
		p->description = "";
		p->min_core_version = 0x1;
		p->plugin_version = 0x1;
		p->type = sge::PT_PicLoader;
	}

	DLLEXPORT sge::pic_loader* create_pic_loader()
	{
		return new sge::cximage::pic_loader();
	}
}
