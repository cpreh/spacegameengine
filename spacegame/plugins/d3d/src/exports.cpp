#include "../../../core/main/dllapi.hpp"
#include "../../../core/main/plugin_manager.hpp"
#include "../renderer_system.hpp"

extern "C"
{
	SGEDLLEXPORT void plugin_version_info(sge::plugin_info* p)
	{
		if(!p)
			return;
		p->name = "Direct3D renderer plugin";
		p->description = "";
		p->plugin_version = 0x1;
		p->min_core_version = 0x1;
		p->type = sge::PT_Renderer;
	}

	SGEDLLEXPORT sge::renderer_system* create_rend_system()
	{
		return new sge::d3d::renderer_system();
	}
}
