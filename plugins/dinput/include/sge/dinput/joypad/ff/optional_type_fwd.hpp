//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_JOYPAD_FF_OPTIONAL_TYPE_FWD_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_FF_OPTIONAL_TYPE_FWD_HPP_INCLUDED

#include <sge/input/joypad/ff/type_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace dinput
{
namespace joypad
{
namespace ff
{

typedef
fcppt::optional::object<
	sge::input::joypad::ff::type
>
optional_type;

}
}
}
}

#endif
