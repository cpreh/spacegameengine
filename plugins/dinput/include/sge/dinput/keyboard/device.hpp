//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_DINPUT_KEYBOARD_DEVICE_HPP_INCLUDED
#define SGE_DINPUT_KEYBOARD_DEVICE_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/object.hpp>
#include <sge/dinput/device/parameters_fwd.hpp>
#include <sge/dinput/keyboard/device_fwd.hpp>
#include <sge/dinput/keyboard/info.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/event/optional_base_unique_ptr_fwd.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace dinput
{
namespace keyboard
{

class device : public sge::input::keyboard::device,
               public sge::dinput::device::object,
               public fcppt::enable_shared_from_this<sge::dinput::keyboard::device>
{
  FCPPT_NONCOPYABLE(device);

public:
  explicit device(sge::dinput::device::parameters const &);

  ~device() override;

private:
  sge::window::object &window() const override;

  awl::event::optional_base_unique_ptr on_dispatch(DIDEVICEOBJECTDATA const &) override;

  sge::dinput::keyboard::info const info_;
};

}
}
}

#endif
