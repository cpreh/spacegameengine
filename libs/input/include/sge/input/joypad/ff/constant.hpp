//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_FF_CONSTANT_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_CONSTANT_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/ff/constant_fwd.hpp>
#include <sge/input/joypad/ff/envelope.hpp>
#include <sge/input/joypad/ff/magnitude.hpp>


namespace sge::input::joypad::ff
{

class constant
{
public:
	SGE_INPUT_DETAIL_SYMBOL
	constant(
		sge::input::joypad::ff::magnitude,
		sge::input::joypad::ff::envelope const &
	);

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::magnitude
	magnitude() const;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::envelope const &
	envelope() const;
private:
	sge::input::joypad::ff::magnitude magnitude_;

	sge::input::joypad::ff::envelope envelope_;
};

}

#endif
