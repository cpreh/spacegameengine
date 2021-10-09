//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/const_screen_resources_ref.hpp>
#include <sge/opengl/xrandr/outputs_view.hpp>
#include <sge/opengl/xrandr/screen_resources.hpp>

sge::opengl::xrandr::outputs_view::outputs_view(
    sge::opengl::xrandr::const_screen_resources_ref const _resources)
    : resources_(_resources)
{
}

sge::opengl::xrandr::outputs_view::const_iterator sge::opengl::xrandr::outputs_view::begin() const
{
  return resources_.get().get_ref().outputs;
}

sge::opengl::xrandr::outputs_view::const_iterator sge::opengl::xrandr::outputs_view::end() const
{
  return this->begin() + resources_.get().get_ref().noutput;
}
