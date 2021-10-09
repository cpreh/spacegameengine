//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_CURSOR_GRAB_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_GRAB_HPP_INCLUDED

#include <sge/x11input/cursor/grab_fwd.hpp>
#include <sge/x11input/device/id.hpp>
#include <awl/backends/x11/cursor/object_ref.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::x11input::cursor
{

class grab
{
  FCPPT_NONMOVABLE(grab);

public:
  grab(
      awl::backends::x11::window::const_base_ref,
      sge::x11input::device::id,
      awl::backends::x11::cursor::object_ref);

  ~grab();

private:
  awl::backends::x11::window::const_base_ref const window_;

  sge::x11input::device::id const id_;
};

}

#endif
