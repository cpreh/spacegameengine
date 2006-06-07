#include "../../../core/main/dllapi.hpp"
#include "../../../core/main/plugin_manager.hpp"
#include "../input_system.hpp"

extern "C"
{
	SGEDLLEXPORT void plugin_version_info(sge::plugin_info* p)
	{
		if(!p)
			return;
		p->name = "direct input plugin";
		p->description = "";
		p->min_core_version = 0x1;
		p->plugin_version = 0x1;
		p->type = sge::PT_Input;
	}

	SGEDLLEXPORT sge::input_system* create_input_system(const sge::window_ptr w)
	{
		ptr_cast<win32_window*>(w.get());
		sge::win32_window_ptr ww = boost::dynamic_pointer_cast<win32_window_ptr>(w);
		return new sge::dinput::input_system(w);
	}
}
