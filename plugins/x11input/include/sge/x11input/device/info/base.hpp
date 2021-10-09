//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_DEVICE_INFO_BASE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INFO_BASE_HPP_INCLUDED

#include <sge/x11input/device/id.hpp>
#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::device::info
{

class base
{
  FCPPT_NONMOVABLE(base);

public:
  using size_type = int;

  base(awl::backends::x11::display_ref, sge::x11input::device::id);

  ~base();

  [[nodiscard]] XIDeviceInfo const *get() const;

  [[nodiscard]] size_type size() const;

private:
  int size_;

  XIDeviceInfo *const devices_;
};

}

#endif
