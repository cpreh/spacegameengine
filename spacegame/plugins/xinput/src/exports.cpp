#include "../input_system.hpp"
#include "../../../core/main/plugin.hpp"
#include "../../../core/main/x_window.hpp"
#include "../../../core/main/ptr_cast.hpp"

extern "C"
{

void plugin_version_info(sge::plugin_info* i)
{
	if(!i)
		return;
	i->name = "X input plugin";
	i->description = "";
	i->type = sge::PT_Input;
	i->plugin_version = 0x1;
	i->min_core_version = 0x1;
}

sge::input_system* create_input_system(sge::window_ptr w)
{
	if(!w)
		throw std::logic_error("xinput plugin's window parameter may not be 0!");
	sge::ptr_cast<sge::x_window*>(w.get());
	return new sge::xinput::input_system(sge::dynamic_pointer_cast<sge::x_window_ptr::value_type>(w));
}

}
