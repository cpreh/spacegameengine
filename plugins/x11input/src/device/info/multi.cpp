//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/info/multi.hpp>
#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::device::info::multi::multi(awl::backends::x11::display_ref const _display)
    : info_base_(_display, sge::x11input::device::id(XIAllDevices))
{
}

sge::x11input::device::info::multi::~multi() = default;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

sge::x11input::device::info::multi::iterator sge::x11input::device::info::multi::begin() const
{
  return info_base_.get();
}

sge::x11input::device::info::multi::iterator sge::x11input::device::info::multi::end() const
{
  return info_base_.get() + // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
         info_base_.size();
}

FCPPT_PP_POP_WARNING
