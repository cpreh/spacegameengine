//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_JOYPAD_FF_EFFECT_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_FF_EFFECT_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/ff/dinput_effect_unique_ptr.hpp>
#include <sge/dinput/joypad/ff/scoped_download.hpp>
#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/optional_play_count_fwd.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace dinput
{
namespace joypad
{
namespace ff
{

class effect : public sge::input::joypad::ff::effect
{
  FCPPT_NONCOPYABLE(effect);

public:
  effect(
      IDirectInputDevice8 &,
      sge::dinput::joypad::button_map const &,
      sge::input::joypad::ff::parameters const &);

  ~effect() override;

private:
  void play(sge::input::joypad::ff::optional_play_count) override;

  void stop() override;

  sge::dinput::joypad::ff::dinput_effect_unique_ptr const effect_;

  sge::dinput::joypad::ff::scoped_download const download_;
};

}
}
}
}

#endif
