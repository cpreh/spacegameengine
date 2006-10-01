#ifndef SGE_DINPUT_KEYBOARD_HPP_INCLUDED
#define SGE_DINPUT_KEYBOARD_HPP_INCLUDED

#include <map>
#include "./input_device.hpp"
#include "./key_converter.hpp"
#include "./di.hpp"

namespace sge
{
	namespace dinput
	{
		class keyboard : public input_device {
		public:
			keyboard(dinput_ptr, const std::string& name, GUID guid, unsigned index, HWND wnd, const key_converter& conv);
			void process_input();
			void get_input(input_array& v);
			key_state query_key(const std::string& name);
		private:
			static BOOL CALLBACK enum_keyboard_keys(LPCDIDEVICEOBJECTINSTANCE ddoi, LPVOID ref);
			typedef std::map<unsigned,key_type> key_map;
			key_map keys;
			const key_converter& conv;
		};
	}
}

#endif
