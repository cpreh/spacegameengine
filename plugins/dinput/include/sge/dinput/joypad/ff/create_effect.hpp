//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_JOYPAD_FF_CREATE_EFFECT_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_FF_CREATE_EFFECT_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/dinput_effect_unique_ptr.hpp>


namespace sge
{
namespace dinput
{
namespace joypad
{
namespace ff
{

sge::dinput::joypad::ff::dinput_effect_unique_ptr
create_effect(
	IDirectInputDevice8 &,
	REFGUID,
	DIEFFECT const &
);

}
}
}
}

#endif
