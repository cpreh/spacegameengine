//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/program/object_ref.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/vector4.hpp>
#include <sge/scenic/impl/render_context/cg/any_color_to_vector4.hpp>
#include <sge/scenic/render_context/cg/light/directional.hpp>
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/optional/maybe_void.hpp>

namespace
{
sge::shader::parameter::name
param_name(sge::scenic::render_context::cg::light::index const &_index, std::string const &_suffix)
{
  return sge::shader::parameter::name(
      "directional_lights[" + fcppt::output_to_std_string(_index.get()) + "]." + _suffix);
}
}

sge::scenic::render_context::cg::light::directional::directional(
    sge::cg::program::object_ref const _program,
    sge::scenic::render_context::cg::light::index const &_index)
    : diffuse_color_(
          _program,
          param_name(_index, "diffuse_color"),
          fcppt::math::vector::null<sge::renderer::vector4>()),
      specular_color_(
          _program,
          param_name(_index, "specular_color"),
          fcppt::math::vector::null<sge::renderer::vector4>()),
      ambient_color_(
          _program,
          param_name(_index, "ambient_color"),
          fcppt::math::vector::null<sge::renderer::vector4>()),
      camera_space_direction_(
          _program,
          param_name(_index, "camera_space_direction"),
          fcppt::math::vector::null<sge::renderer::vector3>())
{
}

void sge::scenic::render_context::cg::light::directional::diffuse_color(
    sge::scenic::render_context::diffuse_color const &_diffuse_color)
{
  diffuse_color_.set(
      sge::scenic::impl::render_context::cg::any_color_to_vector4(_diffuse_color.get()));
}

void sge::scenic::render_context::cg::light::directional::specular_color(
    sge::scenic::render_context::specular_color const &_specular_color)
{
  specular_color_.set(
      sge::scenic::impl::render_context::cg::any_color_to_vector4(_specular_color.get()));
}

void sge::scenic::render_context::cg::light::directional::ambient_color(
    sge::scenic::render_context::ambient_color const &_ambient_color)
{
  ambient_color_.set(
      sge::scenic::impl::render_context::cg::any_color_to_vector4(_ambient_color.get()));
}

void sge::scenic::render_context::cg::light::directional::camera_space_direction(
    sge::scenic::render_context::light::direction const &_camera_space_direction)
{
  fcppt::optional::maybe_void(
      fcppt::math::vector::normalize(_camera_space_direction.get()),
      [this](sge::renderer::vector3 const _direction)
      { this->camera_space_direction_.set(_direction); });
}

sge::scenic::render_context::cg::light::directional::~directional() = default;
