//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_FF_EFFECT_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_EFFECT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/ff/effect_fwd.hpp>
#include <sge/input/joypad/ff/optional_play_count_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace input
{
namespace joypad
{
namespace ff
{

class SGE_CORE_DETAIL_CLASS_SYMBOL effect
{
	FCPPT_NONMOVABLE(
		effect
	);
protected:
	SGE_INPUT_DETAIL_SYMBOL
	effect();
public:
	SGE_INPUT_DETAIL_SYMBOL
	virtual
	~effect();

	virtual
	void
	play(
		sge::input::joypad::ff::optional_play_count
	) = 0;

	virtual
	void
	stop() = 0;
};

}
}
}
}

#endif
