#include "../../../plugin.hpp"
#include "../font_system.hpp"

extern "C"
{

void plugin_version_info(sge::plugin_info* const p)
{
	if(!p)
		return;
	p->name = "freetype font plugin";
	p->description = "";
	p->min_core_version = 0x1;
	p->plugin_version = 0x1;
	p->type = sge::PT_Font;
}

sge::font_system* create_font_system()
{
	return new sge::ft::font_system();
}

}
