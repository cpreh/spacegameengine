//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_DEVICE_INFO_SINGLE_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INFO_SINGLE_HPP_INCLUDED

#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/info/const_optional_ref.hpp>
#include <sge/x11input/device/info/multi.hpp>
#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::device::info
{

class single
{
  FCPPT_NONMOVABLE(single);

public:
  single(awl::backends::x11::display_ref, sge::x11input::device::id);

  ~single();

  [[nodiscard]] sge::x11input::device::info::const_optional_ref get() const;

private:
  sge::x11input::device::info::multi info_base_;

  sge::x11input::device::info::const_optional_ref const info_;
};

}

#endif
