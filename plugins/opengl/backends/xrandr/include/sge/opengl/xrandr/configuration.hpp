//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_XRANDR_CONFIGURATION_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_CONFIGURATION_HPP_INCLUDED

#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::xrandr
{

class configuration
{
  FCPPT_NONMOVABLE(configuration);

public:
  explicit configuration(awl::backends::x11::window::const_base_ref);

  ~configuration();

  [[nodiscard]] XRRScreenConfiguration *get() const;

private:
  XRRScreenConfiguration *const config_;
};

}

#endif
