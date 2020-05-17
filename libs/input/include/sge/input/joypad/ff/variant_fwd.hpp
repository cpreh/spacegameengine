//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_FF_VARIANT_FWD_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_VARIANT_FWD_HPP_INCLUDED

#include <sge/input/joypad/ff/condition_fwd.hpp>
#include <sge/input/joypad/ff/constant_fwd.hpp>
#include <sge/input/joypad/ff/periodic_fwd.hpp>
#include <sge/input/joypad/ff/ramp_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>


namespace sge
{
namespace input
{
namespace joypad
{
namespace ff
{

using
variant
=
fcppt::variant::object<
	sge::input::joypad::ff::constant,
	sge::input::joypad::ff::ramp,
	sge::input::joypad::ff::periodic,
	sge::input::joypad::ff::condition
>;

}
}
}
}

#endif
