//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/ff/create_effect.hpp>
#include <sge/dinput/joypad/ff/dinput_effect_unique_ptr.hpp>
#include <sge/dinput/joypad/ff/effect.hpp>
#include <sge/dinput/joypad/ff/start.hpp>
#include <sge/dinput/joypad/ff/stop.hpp>
#include <sge/dinput/joypad/ff/variant_to_guid.hpp>
#include <sge/dinput/joypad/ff/with_parameters.hpp>
#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/optional_play_count.hpp>
#include <sge/input/joypad/ff/parameters.hpp>
#include <fcppt/function_impl.hpp>


sge::dinput::joypad::ff::effect::effect(
	IDirectInputDevice8 &_device,
	sge::dinput::joypad::button_map const &_button_map,
	sge::input::joypad::ff::parameters const &_parameters
)
:
	sge::input::joypad::ff::effect(),
	effect_{
		sge::dinput::joypad::ff::with_parameters(
			_button_map,
			_parameters,
			fcppt::function<
				sge::dinput::joypad::ff::dinput_effect_unique_ptr (
					DIEFFECT const &
				)
			>{
				[
					&_device,
					&_parameters
				](
					DIEFFECT const &_effect
				)
				{
					return
						sge::dinput::joypad::ff::create_effect(
							_device,
							sge::dinput::joypad::ff::variant_to_guid(
								_parameters.variant()
							),
							_effect
						);
				}
			}
		)
	},
	download_{
		*effect_
	}
{
}

sge::dinput::joypad::ff::effect::~effect()
{
}

void
sge::dinput::joypad::ff::effect::play(
	sge::input::joypad::ff::optional_play_count const _play_count
)
{
	sge::dinput::joypad::ff::start(
		*effect_,
		_play_count
	);
}

void
sge::dinput::joypad::ff::effect::stop()
{
	sge::dinput::joypad::ff::stop(
		*effect_
	);
}
