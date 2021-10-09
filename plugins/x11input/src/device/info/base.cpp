//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/info/base.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::device::info::base::base(
    awl::backends::x11::display_ref const _display, sge::x11input::device::id const _id)
    : size_(0), devices_(::XIQueryDevice(_display.get().get(), _id.get(), &size_))
{
  if (devices_ == nullptr)
  {
    throw sge::input::exception{FCPPT_TEXT("XIQueryDevice failed!")};
  }
}

sge::x11input::device::info::base::~base() { ::XIFreeDeviceInfo(devices_); }

XIDeviceInfo const *sge::x11input::device::info::base::get() const { return devices_; }

sge::x11input::device::info::base::size_type sge::x11input::device::info::base::size() const
{
  return size_;
}
