//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_XRANDR_CRTCS_VIEW_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_CRTCS_VIEW_HPP_INCLUDED

#include <sge/opengl/xrandr/const_screen_resources_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::xrandr
{

class crtcs_view
{
public:
  explicit crtcs_view(sge::opengl::xrandr::const_screen_resources_ref);

  using const_iterator = RRCrtc const *;

  [[nodiscard]] const_iterator begin() const;

  [[nodiscard]] const_iterator end() const;

private:
  sge::opengl::xrandr::const_screen_resources_ref resources_;
};

}

#endif
