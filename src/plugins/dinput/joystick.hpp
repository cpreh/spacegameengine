#ifndef SGE_DINPUT_JOYSTICK_HPP_INCLUDED
#define SGE_DINPUT_JOYSTICK_HPP_INCLUDED

#include <map>
#include "./input_device.hpp"
#include "./di.hpp"

namespace sge
{
	namespace dinput
	{
		class joystick : public input_device {
		public:
			joystick(dinput_ptr di, GUID guid, unsigned index, HWND wnd);
			void get_input(input_array& a);
		private:
			static BOOL CALLBACK enum_joystick_keys(LPCDIDEVICEOBJECTINSTANCE ddoi, LPVOID ref);
			typedef std::map<unsigned,key_type> key_map;
			key_map  keys;
			key_map  l_keys;
			key_map  r_keys;
		};
	}
}

#endif
