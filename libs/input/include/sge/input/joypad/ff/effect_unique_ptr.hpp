//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_FF_EFFECT_UNIQUE_PTR_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_EFFECT_UNIQUE_PTR_HPP_INCLUDED

#include <sge/input/joypad/ff/effect_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>


namespace sge
{
namespace input
{
namespace joypad
{
namespace ff
{

typedef
fcppt::unique_ptr<
	sge::input::joypad::ff::effect
>
effect_unique_ptr;

}
}
}
}

#endif
