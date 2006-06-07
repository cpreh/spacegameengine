#include <vector>
#include "../keyboard.hpp"

sge::dinput::keyboard::keyboard(const dinput_ptr di, const std::string& name, const GUID guid, const unsigned index, const win32_window_ptr wnd, const key_converter& conv)
: input_device(di,name,guid,index,wnd), conv(conv)
{
	set_data_format(&c_dfDIKeyboard);
	enum_objects(enum_keyboard_keys);
	acquire();
}

void sge::dinput::keyboard::get_input(input_array& v)
{
	input_buffer data;
	DWORD elements;
	if(!_get_input(data,elements))
		return;
	for(unsigned i = 0; i < elements; ++i)
		v.push_back(key_pair(keys[data[i].dwOfs],data[i].dwData & 0x80 ? 1.f : 0));
}

BOOL sge::dinput::keyboard::enum_keyboard_keys(LPCDIDEVICEOBJECTINSTANCE ddoi,  LPVOID s)
{
	keyboard& k = *static_cast<keyboard*>(s);
	k.keys[ddoi->dwOfs] = key_type(ddoi->tszName,k.get_name(),k.get_index(),k.conv.create_key_code(ddoi->dwOfs));
	return DIENUM_CONTINUE;
}
