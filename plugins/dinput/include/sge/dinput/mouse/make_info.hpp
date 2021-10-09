//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_MOUSE_MAKE_INFO_HPP_INCLUDED
#define SGE_DINPUT_MOUSE_MAKE_INFO_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/mouse/info_fwd.hpp>
#include <sge/input/info/name.hpp>

namespace sge
{
namespace dinput
{
namespace mouse
{

sge::dinput::mouse::info make_info(IDirectInputDevice8 &, sge::input::info::name const &);

}
}
}

#endif
