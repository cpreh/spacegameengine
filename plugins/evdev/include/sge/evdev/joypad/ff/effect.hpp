//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_EVDEV_JOYPAD_FF_EFFECT_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_EFFECT_HPP_INCLUDED

#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/joypad/button/event_map.hpp>
#include <sge/evdev/joypad/ff/uploaded_effect.hpp>
#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/optional_play_count_fwd.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{
namespace ff
{

class effect
:
	public
		sge::input::joypad::ff::effect
{
	FCPPT_NONCOPYABLE(
		effect
	);
public:
	effect(
		sge::evdev::device::fd const &,
		sge::evdev::joypad::button::event_map const &,
		sge::input::joypad::ff::parameters const &
	);

	~effect()
	override;

	void
	play(
		sge::input::joypad::ff::optional_play_count
	)
	override;

	void
	stop()
	override;
private:
	sge::evdev::device::fd const &fd_;

	sge::evdev::joypad::ff::uploaded_effect const uploaded_effect_;
};

}
}
}
}

#endif
