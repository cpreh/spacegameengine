//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/extension.hpp>

sge::opengl::xrandr::extension::extension(event_base_type const _event_base)
    : event_base_(_event_base)
{
}

sge::opengl::xrandr::extension::event_base_type sge::opengl::xrandr::extension::event_base() const
{
  return event_base_;
}
