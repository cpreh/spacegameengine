//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_FF_ENVELOPE_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_ENVELOPE_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/ff/attack_level.hpp>
#include <sge/input/joypad/ff/attack_time.hpp>
#include <sge/input/joypad/ff/envelope_fwd.hpp>
#include <sge/input/joypad/ff/fade_level.hpp>
#include <sge/input/joypad/ff/fade_time.hpp>


namespace sge
{
namespace input
{
namespace joypad
{
namespace ff
{

class envelope
{
public:
	SGE_INPUT_DETAIL_SYMBOL
	envelope(
		sge::input::joypad::ff::attack_level,
		sge::input::joypad::ff::attack_time,
		sge::input::joypad::ff::fade_level,
		sge::input::joypad::ff::fade_time
	);

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::attack_level
	attack_level() const;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::attack_time
	attack_time() const;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::fade_level
	fade_level() const;

	[[nodiscard]]
	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::fade_time
	fade_time() const;
private:
	sge::input::joypad::ff::attack_level attack_level_;

	sge::input::joypad::ff::attack_time attack_time_;

	sge::input::joypad::ff::fade_level fade_level_;

	sge::input::joypad::ff::fade_time fade_time_;
};

}
}
}
}

#endif
