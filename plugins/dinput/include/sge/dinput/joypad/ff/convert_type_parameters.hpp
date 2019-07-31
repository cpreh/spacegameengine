//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_JOYPAD_FF_CONVERT_TYPE_PARAMETERS_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_FF_CONVERT_TYPE_PARAMETERS_HPP_INCLUDED

#include <sge/dinput/joypad/ff/type_parameters.hpp>
#include <sge/input/joypad/ff/variant_fwd.hpp>


namespace sge
{
namespace dinput
{
namespace joypad
{
namespace ff
{

sge::dinput::joypad::ff::type_parameters
convert_type_parameters(
	sge::input::joypad::ff::variant const &
);

}
}
}
}

#endif
