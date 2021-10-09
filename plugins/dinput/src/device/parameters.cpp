//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/parameters.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/windows/system/event/handle_fwd.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>

sge::dinput::device::parameters::parameters(
    IDirectInput8 &_instance,
    GUID const _guid,
    sge::window::object &_sge_window,
    awl::backends::windows::window::object &_window,
    awl::backends::windows::system::event::handle &_event_handle)
    : instance_{_instance},
      guid_{_guid},
      sge_window_{_sge_window},
      window_{_window},
      event_handle_{_event_handle}
{
}

IDirectInput8 &sge::dinput::device::parameters::instance() const { return instance_.get(); }

GUID sge::dinput::device::parameters::guid() const { return guid_; }

sge::window::object &sge::dinput::device::parameters::sge_window() const
{
  return sge_window_.get();
}

awl::backends::windows::window::object &sge::dinput::device::parameters::window() const
{
  return window_.get();
}

awl::backends::windows::system::event::handle &sge::dinput::device::parameters::event_handle() const
{
  return event_handle_.get();
}
