//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/ortho_freelook/optional_projection_rectangle.hpp>
#include <sge/camera/ortho_freelook/pan_speed.hpp>
#include <sge/camera/ortho_freelook/parameters.hpp>
#include <sge/camera/ortho_freelook/zoom_speed.hpp>
#include <sge/camera/ortho_freelook/action/mapping.hpp>
#include <sge/camera/ortho_freelook/action/wsg_mapping.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/rect.hpp>
#include <fcppt/math/vector/fill.hpp>

sge::camera::ortho_freelook::parameters::parameters(
    sge::renderer::projection::near const _near,
    sge::renderer::projection::far const _far)
    : zoom_speed_{fcppt::math::vector::fill<sge::renderer::vector2>(
          0.30F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          )},
      pan_speed_{fcppt::math::vector::fill<sge::renderer::vector2>(
          0.01F // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          )},
      projection_rectangle_{},
      near_{_near},
      far_{_far},
      action_mapping_{sge::camera::ortho_freelook::action::wsg_mapping()}
{
}

sge::camera::ortho_freelook::parameters &sge::camera::ortho_freelook::parameters::zoom_speed(
    sge::camera::ortho_freelook::zoom_speed const _zoom_speed)
{
  zoom_speed_ = _zoom_speed;

  return *this;
}

sge::camera::ortho_freelook::zoom_speed sge::camera::ortho_freelook::parameters::zoom_speed() const
{
  return zoom_speed_;
}

sge::camera::ortho_freelook::parameters &sge::camera::ortho_freelook::parameters::action_mapping(
    sge::camera::ortho_freelook::action::mapping const &_action_mapping)
{
  action_mapping_ = _action_mapping;

  return *this;
}

sge::camera::ortho_freelook::action::mapping const &
sge::camera::ortho_freelook::parameters::action_mapping() const
{
  return action_mapping_;
}

sge::camera::ortho_freelook::parameters &sge::camera::ortho_freelook::parameters::pan_speed(
    sge::camera::ortho_freelook::pan_speed const _pan_speed)
{
  pan_speed_ = _pan_speed;

  return *this;
}

sge::camera::ortho_freelook::pan_speed sge::camera::ortho_freelook::parameters::pan_speed() const
{
  return pan_speed_;
}

sge::camera::ortho_freelook::parameters &
sge::camera::ortho_freelook::parameters::projection_rectangle(
    sge::renderer::projection::rect const &_projection_rectangle)
{
  projection_rectangle_ =
      sge::camera::ortho_freelook::optional_projection_rectangle(_projection_rectangle);

  return *this;
}

sge::camera::ortho_freelook::optional_projection_rectangle const &
sge::camera::ortho_freelook::parameters::projection_rectangle() const
{
  return projection_rectangle_;
}

sge::renderer::projection::near sge::camera::ortho_freelook::parameters::near() const
{
  return near_;
}

sge::renderer::projection::far sge::camera::ortho_freelook::parameters::far() const { return far_; }
