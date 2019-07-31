//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_ABSOLUTE_AXIS_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_ABSOLUTE_AXIS_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/absolute_axis_fwd.hpp>
#include <sge/input/joypad/absolute_axis_id.hpp>
#include <sge/input/joypad/axis_code.hpp>


namespace sge
{
namespace input
{
namespace joypad
{

class absolute_axis
{
public:
	SGE_INPUT_DETAIL_SYMBOL
	absolute_axis(
		sge::input::joypad::axis_code,
		sge::input::joypad::absolute_axis_id
	);

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::axis_code
	code() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::absolute_axis_id
	id() const;
private:
	sge::input::joypad::axis_code code_;

	sge::input::joypad::absolute_axis_id id_;
};

}
}
}

#endif
