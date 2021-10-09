//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/update_duration.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/tracking/keyframe.hpp>

sge::camera::tracking::keyframe::keyframe(
    sge::camera::update_duration const &_duration,
    sge::camera::coordinate_system::object const _coordinate_system)
    : duration_(_duration), coordinate_system_(_coordinate_system)
{
}

sge::camera::update_duration const &sge::camera::tracking::keyframe::duration() const
{
  return duration_;
}

sge::camera::coordinate_system::object const &
sge::camera::tracking::keyframe::coordinate_system() const
{
  return coordinate_system_;
}
