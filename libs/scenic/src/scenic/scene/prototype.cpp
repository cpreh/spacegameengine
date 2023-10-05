//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/scenic/render_context/ambient_color.hpp>
#include <sge/scenic/render_context/fog/optional_properties.hpp>
#include <sge/scenic/render_context/light/sequence.hpp>
#include <sge/scenic/scene/camera_properties.hpp>
#include <sge/scenic/scene/entity_sequence.hpp>
#include <sge/scenic/scene/prototype.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::scenic::scene::prototype::prototype(
    sge::scenic::scene::camera_properties const _camera,
    sge::scenic::render_context::fog::optional_properties _fog,
    sge::scenic::render_context::ambient_color _ambient_color)
    : camera_(_camera),
      fog_(std::move(_fog)),
      ambient_color_(std::move(_ambient_color)),
      entities_(),
      lights_()
{
}

sge::scenic::scene::entity_sequence const &sge::scenic::scene::prototype::entities() const
{
  return entities_;
}

sge::scenic::scene::entity_sequence &sge::scenic::scene::prototype::entities() { return entities_; }

sge::scenic::render_context::light::sequence const &sge::scenic::scene::prototype::lights() const
{
  return lights_;
}

sge::scenic::render_context::light::sequence &sge::scenic::scene::prototype::lights()
{
  return lights_;
}

sge::scenic::scene::camera_properties const &sge::scenic::scene::prototype::camera() const
{
  return camera_;
}

sge::scenic::render_context::fog::optional_properties const &
sge::scenic::scene::prototype::fog() const
{
  return fog_;
}

sge::scenic::render_context::ambient_color const &
sge::scenic::scene::prototype::ambient_color() const
{
  return ambient_color_;
}

sge::scenic::scene::prototype::~prototype() = default;
