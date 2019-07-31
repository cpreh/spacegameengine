//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_JOYPAD_INFO_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_INFO_HPP_INCLUDED

#include <sge/dinput/joypad/absolute_axis_map.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/info_fwd.hpp>
#include <sge/dinput/joypad/relative_axis_map.hpp>
#include <sge/input/joypad/info.hpp>


namespace sge
{
namespace dinput
{
namespace joypad
{

class info
{
public:
	info(
		sge::input::joypad::info const &,
		sge::dinput::joypad::absolute_axis_map const &,
		sge::dinput::joypad::button_map const &,
		sge::dinput::joypad::relative_axis_map const &
	);

	sge::input::joypad::info const &
	input_info() const;

	sge::dinput::joypad::absolute_axis_map const &
	absolute_axis_map() const;

	sge::dinput::joypad::button_map const &
	button_map() const;

	sge::dinput::joypad::relative_axis_map const &
	relative_axis_map() const;
private:
	sge::input::joypad::info input_info_;

	sge::dinput::joypad::absolute_axis_map absolute_axis_map_;

	sge::dinput::joypad::button_map button_map_;

	sge::dinput::joypad::relative_axis_map relative_axis_map_;
};

}
}
}

#endif
