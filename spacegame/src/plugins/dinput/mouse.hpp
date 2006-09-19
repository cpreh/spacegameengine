#ifndef SGE_DINPUT_MOUSE_HPP_INCLUDED
#define SGE_DINPUT_MOUSE_HPP_INCLUDED

#include <map>
#include "./input_device.hpp"
#include "./di.hpp"

namespace sge
{
	namespace dinput
	{
		class mouse : public input_device {
		public:
			mouse(dinput_ptr di, const std::string& name, GUID guid, unsigned index, HWND wnd);
			void get_input(input_array& v);
		private:
			static BOOL CALLBACK enum_mouse_keys(LPCDIDEVICEOBJECTINSTANCE ddoi, LPVOID ref);
			typedef std::map<unsigned,key_type> key_map;
			key_map  keys;
			key_map  l_keys;
			key_map  r_keys;
		};
	}
}

#endif
