//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_JOYPAD_DEVICE_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_DEVICE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/device_fwd.hpp>
#include <sge/input/joypad/info_fwd.hpp>
#include <sge/input/joypad/ff/effect_unique_ptr.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace input
{
namespace joypad
{

class SGE_CORE_DETAIL_CLASS_SYMBOL device
{
	FCPPT_NONMOVABLE(
		device
	);
protected:
	SGE_INPUT_DETAIL_SYMBOL
	device();
public:
	SGE_INPUT_DETAIL_SYMBOL
	virtual
	~device();

	[[nodiscard]]
	virtual
	sge::window::object &
	window() const = 0;

	[[nodiscard]]
	virtual
	sge::input::joypad::info const &
	info() const = 0;

	[[nodiscard]]
	virtual
	sge::input::joypad::ff::effect_unique_ptr
	create_ff_effect(
		sge::input::joypad::ff::parameters const &
	) = 0;
};

}
}
}

#endif
