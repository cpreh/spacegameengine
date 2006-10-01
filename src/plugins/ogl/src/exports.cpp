#include "../../../plugin.hpp"
#include "../renderer_system.hpp"

extern "C"
{

void plugin_version_info(sge::plugin_info* const p)
{
	if(!p)
		return;
	p->name = "opengl renderer plugin";
	p->description = "";
	p->plugin_version = 0x1;
	p->min_core_version = 0x1;
	p->type = sge::PT_Renderer;
}

sge::renderer_system* create_renderer_system()
{
	return new sge::ogl::renderer_system();
}

}
