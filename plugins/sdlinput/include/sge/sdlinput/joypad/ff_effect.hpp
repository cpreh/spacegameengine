//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SDLINPUT_JOYPAD_FF_EFFECT_HPP_INCLUDED
#define SGE_SDLINPUT_JOYPAD_FF_EFFECT_HPP_INCLUDED

#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/optional_play_count_fwd.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_joystick.h>
#include <fcppt/config/external_end.hpp>

namespace sge::sdlinput::joypad
{

class ff_effect : public sge::input::joypad::ff::effect
{
  FCPPT_NONMOVABLE(ff_effect);

public:
  ff_effect(
      SDL_Joystick &, // NOLINT(google-runtime-references)
      sge::input::joypad::ff::parameters const &);

  ~ff_effect() override;

  void play(sge::input::joypad::ff::optional_play_count) override;

  void stop() override;
};

}

#endif
