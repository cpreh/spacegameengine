//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WLINPUT_CURSOR_HOLDER_HPP_INCLUDED
#define SGE_WLINPUT_CURSOR_HOLDER_HPP_INCLUDED

#include <awl/backends/wayland/seat_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-client-protocol.h>
#include <fcppt/config/external_end.hpp>

namespace sge::wlinput::cursor
{

class holder
{
  FCPPT_NONMOVABLE(holder);

public:
  explicit holder(awl::backends::wayland::seat_ref);

  ~holder();

  [[nodiscard]] wl_pointer *get() const;

private:
  wl_pointer *const impl_;
};

}

#endif
