//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_SHARED_PTR_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_SHARED_PTR_HPP_INCLUDED

#include <sge/input/joypad/device_fwd.hpp>
#include <fcppt/shared_ptr_impl.hpp>


namespace sge
{
namespace input
{
namespace joypad
{

typedef
fcppt::shared_ptr<
	sge::input::joypad::device
>
shared_ptr;

}
}
}

#endif
