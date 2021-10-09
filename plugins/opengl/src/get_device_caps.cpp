//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/get_device_caps.hpp>
#include <sge/opengl/get_int.hpp>
#include <sge/opengl/get_string.hpp>
#include <sge/opengl/srgb_context.hpp>
#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_config.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_context.hpp>
#include <sge/opengl/state/core/sampler/filter/optional_anisotropy_config.hpp>
#include <sge/opengl/texture/multi_config.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/npot_context.hpp>
#include <sge/opengl/texture/optional_multi_config.hpp>
#include <sge/opengl/texture/optional_volume_config.hpp>
#include <sge/opengl/texture/volume_config.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/caps/clip_plane_indices.hpp>
#include <sge/renderer/caps/description.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/caps/driver_name.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/max_anisotropy.hpp>
#include <sge/renderer/caps/max_texture_size.hpp>
#include <sge/renderer/caps/max_volume_texture_extent.hpp>
#include <sge/renderer/caps/non_power_of_2_textures.hpp>
#include <sge/renderer/caps/normalized_cvv.hpp>
#include <sge/renderer/caps/render_target_inverted.hpp>
#include <sge/renderer/caps/render_target_supported.hpp>
#include <sge/renderer/caps/srgb_framebuffer.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <fcppt/const.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/optional/maybe.hpp>

sge::renderer::caps::device sge::opengl::get_device_caps(sge::opengl::context::object &_context)
{
  sge::opengl::state::core::sampler::filter::optional_anisotropy_config const &anisotropy_config(
      sge::opengl::context::use<sge::opengl::state::core::sampler::filter::anisotropy_context>(
          fcppt::make_ref(_context), _context.info())
          .config());

  sge::opengl::texture::optional_multi_config const &texture_multi_config(
      sge::opengl::context::use<sge::opengl::texture::multi_context>(
          fcppt::make_ref(_context), _context.info())
          .config());

  sge::opengl::texture::optional_volume_config const &volume_texture_config(
      sge::opengl::context::use<sge::opengl::texture::volume_context>(
          fcppt::make_ref(_context), _context.info())
          .config());

  sge::renderer::caps::render_target_supported const render_target_supported(
      sge::opengl::context::use<sge::opengl::fbo::context>(
          fcppt::make_ref(_context), _context.info())
          .config()
          .has_value());

  return sge::renderer::caps::device(
      sge::renderer::caps::driver_name(fcppt::from_std_string(sge::opengl::get_string(GL_VENDOR))),
      sge::renderer::caps::description(
          fcppt::from_std_string(sge::opengl::get_string(GL_RENDERER)) + FCPPT_TEXT(' ') +
          fcppt::from_std_string(sge::opengl::get_string(GL_VERSION))),
      sge::renderer::caps::normalized_cvv(true),
      sge::renderer::caps::max_texture_size(
          fcppt::math::dim::fill<sge::renderer::dim2>(fcppt::cast::size<sge::renderer::size_type>(
              fcppt::cast::to_unsigned(sge::opengl::get_int(GL_MAX_TEXTURE_SIZE))))),
      sge::renderer::caps::max_volume_texture_extent(
          fcppt::cast::to_unsigned(fcppt::optional::maybe(
              volume_texture_config,
              fcppt::const_(0),
              [](sge::opengl::texture::volume_config const &_config)
              { return sge::opengl::get_int(_config.max_extent_flag()); }))),
      sge::renderer::caps::non_power_of_2_textures(
          sge::opengl::context::use<sge::opengl::texture::npot_context>(
              fcppt::make_ref(_context), _context.info())
              .is_supported()),
      fcppt::strong_typedef_construct_cast<
          sge::renderer::caps::max_anisotropy,
          fcppt::cast::static_cast_fun>(fcppt::optional::maybe(
          anisotropy_config,
          fcppt::const_(0),
          [](sge::opengl::state::core::sampler::filter::anisotropy_config const &_config)
          { return sge::opengl::get_int(_config.max_anisotropy_flag()); })),
      render_target_supported,
      sge::renderer::caps::render_target_inverted(true),
      fcppt::strong_typedef_construct_cast<
          sge::renderer::caps::clip_plane_indices,
          fcppt::cast::static_cast_fun>(sge::opengl::get_int(GL_MAX_CLIP_PLANES)),
      fcppt::strong_typedef_construct_cast<
          sge::renderer::caps::light_indices,
          fcppt::cast::static_cast_fun>(sge::opengl::get_int(GL_MAX_LIGHTS)),
      fcppt::optional::maybe(
          texture_multi_config,
          fcppt::const_(sge::renderer::caps::texture_stages{1U}),
          [](sge::opengl::texture::multi_config const &_config) { return _config.max_level(); }),
      fcppt::strong_typedef_construct_cast<
          sge::renderer::caps::target_surface_indices,
          fcppt::cast::static_cast_fun>(
          render_target_supported.get() ? sge::opengl::get_int(GL_MAX_COLOR_ATTACHMENTS) : 0),
      sge::renderer::caps::srgb_framebuffer(sge::opengl::context::use<sge::opengl::srgb_context>(
                                                fcppt::make_ref(_context), _context.info())
                                                .flag()
                                                .has_value()));
}
