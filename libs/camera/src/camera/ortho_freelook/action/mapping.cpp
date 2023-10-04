//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/ortho_freelook/action/activate_pan.hpp>
#include <sge/camera/ortho_freelook/action/mapping.hpp>
#include <sge/camera/ortho_freelook/action/zoom_in.hpp>
#include <sge/camera/ortho_freelook/action/zoom_out.hpp>

sge::camera::ortho_freelook::action::mapping::mapping(
    sge::camera::ortho_freelook::action::zoom_in const &_zoom_in,
    sge::camera::ortho_freelook::action::zoom_out const &_zoom_out,
    sge::camera::ortho_freelook::action::activate_pan const &_activate_pan)
    : zoom_in_(_zoom_in), zoom_out_(_zoom_out), activate_pan_(_activate_pan)
{
}

sge::camera::ortho_freelook::action::zoom_in const &
sge::camera::ortho_freelook::action::mapping::zoom_in() const
{
  return zoom_in_;
}

sge::camera::ortho_freelook::action::zoom_out const &
sge::camera::ortho_freelook::action::mapping::zoom_out() const
{
  return zoom_out_;
}

sge::camera::ortho_freelook::action::activate_pan const &
sge::camera::ortho_freelook::action::mapping::activate_pan() const
{
  return activate_pan_;
}
