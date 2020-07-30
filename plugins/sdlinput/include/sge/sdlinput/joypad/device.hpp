//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SDLINPUT_JOYPAD_DEVICE_HPP_INCLUDED
#define SGE_SDLINPUT_JOYPAD_DEVICE_HPP_INCLUDED

#include <sge/input/joypad/absolute_axis.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis.hpp>
#include <sge/input/joypad/ff/effect_unique_ptr.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/sdlinput/joypad/ball_direction_fwd.hpp>
#include <sge/sdlinput/joypad/device_fwd.hpp>
#include <sge/sdlinput/joypad/device_id.hpp>
#include <sge/sdlinput/joypad/hat_direction_fwd.hpp>
#include <sge/sdlinput/joypad/instance.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sdlinput
{
namespace joypad
{

class device
:
	public
		sge::input::joypad::device
{
	FCPPT_NONMOVABLE(
		device
	);
public:
	device(
		sge::window::object_ref,
		sge::sdlinput::joypad::device_id
	);

	~device()
	override;

	[[nodiscard]]
	sge::window::object &
	window() const
	override;

	[[nodiscard]]
	sge::input::joypad::info const &
	info() const
	override;

	[[nodiscard]]
	sge::input::joypad::ff::effect_unique_ptr
	create_ff_effect(
		sge::input::joypad::ff::parameters const &
	)
	override;

	[[nodiscard]]
	SDL_JoystickID
	id() const;

	[[nodiscard]]
	sge::input::joypad::absolute_axis
	axis(
		std::uint8_t
	) const;

	[[nodiscard]]
	sge::input::joypad::relative_axis
	ball_axis(
		std::uint8_t,
		sge::sdlinput::joypad::ball_direction
	) const;

	[[nodiscard]]
	sge::input::joypad::absolute_axis
	hat_axis(
		std::uint8_t,
		sge::sdlinput::joypad::hat_direction
	) const;
private:
	sge::sdlinput::joypad::instance const instance_;

	sge::window::object_ref const window_;

	sge::input::joypad::info const info_;
};

}
}
}

#endif
