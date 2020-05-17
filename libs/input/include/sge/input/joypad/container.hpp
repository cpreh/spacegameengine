//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_CONTAINER_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_CONTAINER_HPP_INCLUDED

#include <sge/input/joypad/shared_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace input
{
namespace joypad
{

using
container
=
std::vector<
	sge::input::joypad::shared_ptr
>;

}
}
}

#endif
