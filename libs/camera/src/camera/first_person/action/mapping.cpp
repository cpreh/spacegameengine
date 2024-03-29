//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/first_person/action/backward.hpp>
#include <sge/camera/first_person/action/down.hpp>
#include <sge/camera/first_person/action/forward.hpp>
#include <sge/camera/first_person/action/left.hpp>
#include <sge/camera/first_person/action/mapping.hpp>
#include <sge/camera/first_person/action/right.hpp>
#include <sge/camera/first_person/action/up.hpp>

sge::camera::first_person::action::mapping::mapping(
    sge::camera::first_person::action::left const &_left,
    sge::camera::first_person::action::right const &_right,
    sge::camera::first_person::action::up const &_up,
    sge::camera::first_person::action::down const &_down,
    sge::camera::first_person::action::forward const &_forward,
    sge::camera::first_person::action::backward const &_backward)
    : left_(_left), right_(_right), up_(_up), down_(_down), forward_(_forward), backward_(_backward)
{
}

sge::camera::first_person::action::left const &
sge::camera::first_person::action::mapping::left() const
{
  return left_;
}

sge::camera::first_person::action::right const &
sge::camera::first_person::action::mapping::right() const
{
  return right_;
}

sge::camera::first_person::action::up const &sge::camera::first_person::action::mapping::up() const
{
  return up_;
}

sge::camera::first_person::action::down const &
sge::camera::first_person::action::mapping::down() const
{
  return down_;
}

sge::camera::first_person::action::forward const &
sge::camera::first_person::action::mapping::forward() const
{
  return forward_;
}

sge::camera::first_person::action::backward const &
sge::camera::first_person::action::mapping::backward() const
{
  return backward_;
}
