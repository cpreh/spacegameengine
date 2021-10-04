//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_FF_ID_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_ID_HPP_INCLUDED

#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace sge::evdev::joypad::ff
{

FCPPT_MAKE_STRONG_TYPEDEF(
	std::int16_t,
	id
);

}

#endif
