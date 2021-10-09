//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image2d/traits/dimension.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/basic_lockable_buffer.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/buffer_surface_types.hpp>
#include <sge/opengl/texture/color_format_types.hpp>
#include <sge/opengl/texture/color_surface.hpp>
#include <sge/opengl/texture/cube.hpp>
#include <sge/opengl/texture/cube_basic.hpp>
#include <sge/opengl/texture/cube_config.hpp>
#include <sge/opengl/texture/cube_types.hpp>
#include <sge/opengl/texture/init.hpp>
#include <sge/opengl/texture/scoped_work_binding.hpp>
#include <sge/opengl/texture/surface_config_fwd.hpp>
#include <sge/opengl/texture/surface_context.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/color_buffer/surface.hpp>
#include <sge/renderer/texture/base.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/cube.hpp>
#include <sge/renderer/texture/cube_parameters.hpp>
#include <sge/renderer/texture/cube_side.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/enum/array_impl.hpp>
#include <fcppt/enum/array_init.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::opengl::texture::cube::cube(
    sge::opengl::texture::cube_config const &_config,
    sge::opengl::texture::basic_parameters const &_basic_parameters,
    sge::renderer::texture::cube_parameters const &_parameters)
    : sge::opengl::texture::cube_basic(_basic_parameters, _config.cube_texture_type(), _parameters),
      size_(_parameters.size()),
      sides_(
          [&_config, &_basic_parameters, &_parameters, this]
          {
            sge::opengl::texture::scoped_work_binding const binding(
                _basic_parameters.log(), _basic_parameters.context(), this->type(), this->id());

            sge::opengl::texture::surface_config const &surface_config{
                sge::opengl::context::use<sge::opengl::texture::surface_context>(
                    fcppt::make_ref(_basic_parameters.context()))
                    .config()};

            return fcppt::enum_::array_init<side_array>(
                [&binding, &surface_config, &_config, &_basic_parameters, &_parameters, this](
                    sge::renderer::texture::cube_side const _side)
                {
                  return sge::opengl::texture::init<sge::opengl::texture::cube_types>(
                      binding,
                      _basic_parameters,
                      _parameters,
                      fcppt::make_cref(surface_config),
                      _config.cube_texture_type(),
                      _config.cube_sides()[_side],
                      this->id());
                });
          }())
{
}

FCPPT_PP_POP_WARNING

sge::opengl::texture::cube::~cube() = default;

sge::renderer::size_type sge::opengl::texture::cube::border_size() const { return size_; }

sge::renderer::texture::cube::nonconst_buffer &sge::opengl::texture::cube::level(
    sge::renderer::texture::cube_side const _side,
    sge::renderer::texture::mipmap::level const _level)
{
  return *sides_[_side][_level.get()];
}

sge::renderer::texture::cube::const_buffer const &sge::opengl::texture::cube::level(
    sge::renderer::texture::cube_side const _side,
    sge::renderer::texture::mipmap::level const _level) const
{
  return *sides_[_side][_level.get()];
}

sge::renderer::texture::mipmap::level_count sge::opengl::texture::cube::levels() const
{
  return fcppt::strong_typedef_construct_cast<
      sge::renderer::texture::mipmap::level_count,
      fcppt::cast::size_fun>(sides_[sge::renderer::texture::cube_side::front].size());
}
