//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/optional_play_count.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/sdlinput/joypad/ff_effect.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>

sge::sdlinput::joypad::ff_effect::ff_effect(
    SDL_Joystick & /*_joypad*/, sge::input::joypad::ff::parameters const & /*_parameters*/
    )
    : sge::input::joypad::ff::effect{}
{
}

sge::sdlinput::joypad::ff_effect::~ff_effect() = default;

void sge::sdlinput::joypad::ff_effect::play(
    sge::input::joypad::ff::optional_play_count const _play_count)
{
}

void sge::sdlinput::joypad::ff_effect::stop() {}
