#ifndef SGE_DINPUT_DI_HPP_INCLUDED
#define SGE_DINPUT_DI_HPP_INCLUDED

#include "../../core/main/shared_ptr.hpp"

#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace sge
{
	namespace dinput
	{
		typedef shared_ptr<IDirectInput8,com_deleter> dinput_ptr;
		typedef shared_ptr<IDirectInputDevice8,com_deleter> dinput_device_ptr;
	}
}

#endif
