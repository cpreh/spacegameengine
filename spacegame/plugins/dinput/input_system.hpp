#ifndef SGE_DINPUT_INPUT_SYSTEM_HPP_INCLUDED
#define SGE_DINPUT_INPUT_SYSTEM_HPP_INCLUDED

#include <map>
#include <vector>
#include "../../core/main/window.hpp"
#include "../../core/input/input_system.hpp"
#include "./input_device.hpp"
#include "./key_converter.hpp"
#include "./di.hpp"

namespace sge
{
	namespace dinput
	{
		class input_system : public sge::input_system {
		public:
			input_system(window_ptr w);
			input_array get_input();
		private:
			typedef dinput_device_ptr key_map;
			typedef std::map<std::string,key_map> key_mapper_u;
			typedef std::multimap<std::string,key_map> key_mapper_m;
			typedef std::pair<std::string,key_map> key_map_pair;
			typedef std::vector<input_device_ptr> device_array;
			typedef std::map<key_code,bool> key_code_press_map;
			key_mapper_u       map_u;
			key_mapper_m       map_m;
			key_code_press_map key_codes_pressed;
			device_array       devices;
			key_array          keys;
			dinput_ptr         di;
			win32_window_ptr   wnd;
			unsigned           keyboards;
			unsigned           mice;
			unsigned           joysticks;
			key_converter      key_conv;

			static BOOL CALLBACK di_enum_devices_callback(LPCDIDEVICEINSTANCE ddi, LPVOID s);
		};
	}
}

#endif
