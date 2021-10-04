//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_FF_LEFT_COEFFICIENT_FWD_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_LEFT_COEFFICIENT_FWD_HPP_INCLUDED

#include <sge/input/joypad/ff/signed_value.hpp>
#include <fcppt/make_strong_typedef.hpp>


namespace sge::input::joypad::ff
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::input::joypad::ff::signed_value,
	left_coefficient
);

}

#endif
