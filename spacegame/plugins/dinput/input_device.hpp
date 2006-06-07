#ifndef SGE_DINPUT_INPUT_DEVICE_HPP_INCLUDED
#define SGE_DINPUT_INPUT_DEVICE_HPP_INCLUDED

#include "../../core/input/input_system.hpp"
#include "../../core/input/key_type.hpp"

#include "./di.hpp"

namespace sge
{
	namespace dinput
	{
		class input_device {
		public:
			virtual void get_input(input_array&) = 0;
			virtual ~input_device(){}
		protected:
			input_device(dinput_ptr di, const std::string& name, GUID Guid, unsigned device_index, HWND wnd);
			void acquire();
			void poll();
			void set_data_format(LPCDIDATAFORMAT lpdf);
			void set_property(REFGUID rguidProp, LPCDIPROPHEADER pdiph);

			static const size_t buffer_size = 1024;
			typedef DIDEVICEOBJECTDATA input_buffer[buffer_size];

			bool _get_input(input_buffer buf, DWORD& elements);
			unsigned get_index() const { return index; }
			void enum_objects(LPDIENUMDEVICEOBJECTSCALLBACK fun);
			const std::string& get_name() const { return name; }
		private:
			void set_cooperative_level(HWND hwnd, DWORD flags);
			static const DIPROPDWORD  buffer_settings;
			static const DWORD        coop_level;
			dinput_device_ptr         device;
			unsigned                  index;
			std::string               name;
		};
		typedef shared_ptr<input_device> input_device_ptr;
	}
}

#endif
