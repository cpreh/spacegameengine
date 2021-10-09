//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_JOYPAD_DEVICE_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_DEVICE_HPP_INCLUDED

#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters_fwd.hpp>
#include <sge/dinput/joypad/device_fwd.hpp>
#include <sge/dinput/joypad/info.hpp>
#include <sge/input/info/name.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info_fwd.hpp>
#include <sge/input/joypad/ff/effect_unique_ptr.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/event/optional_base_unique_ptr_fwd.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace dinput
{
namespace joypad
{

class device : public sge::input::joypad::device,
               public sge::dinput::device::object,
               public fcppt::enable_shared_from_this<sge::dinput::joypad::device>
{
  FCPPT_NONCOPYABLE(device);

public:
  device(sge::dinput::device::parameters const &, sge::input::info::name const &);

  ~device() override;

private:
  sge::window::object &window() const override;

  sge::input::joypad::info const &info() const override;

  sge::input::joypad::ff::effect_unique_ptr
  create_ff_effect(sge::input::joypad::ff::parameters const &) override;

  awl::event::optional_base_unique_ptr on_dispatch(DIDEVICEOBJECTDATA const &) override;

  sge::dinput::joypad::info const info_;
};

}
}
}

#endif
