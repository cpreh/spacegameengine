//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_FF_TYPE_FIELD_FWD_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_TYPE_FIELD_FWD_HPP_INCLUDED

#include <sge/input/joypad/ff/type.hpp>
#include <fcppt/container/bitfield/enum_object_fwd.hpp>


namespace sge
{
namespace input
{
namespace joypad
{
namespace ff
{

typedef
fcppt::container::bitfield::enum_object<
	sge::input::joypad::ff::type
>
type_field;

}
}
}
}

#endif
