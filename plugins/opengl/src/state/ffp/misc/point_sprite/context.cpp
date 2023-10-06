//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/ext.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/config.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/context.hpp>
#include <sge/opengl/state/ffp/misc/point_sprite/optional_config.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::opengl::state::ffp::misc::point_sprite::context::context(
    sge::opengl::info::context const &_info)
    : sge::opengl::context::base(),
      config_(
          sge::opengl::info::version_at_least(
              _info.version(),
              sge::opengl::info::major_version{2U},
              sge::opengl::info::minor_version{0U})
              ? sge::opengl::state::ffp::misc::point_sprite::optional_config(
                    sge::opengl::state::ffp::misc::point_sprite::config(
                        // TODO(philipp): Move all strong typedefs out of the class
                        sge::opengl::state::ffp::misc::point_sprite::config::point_sprite_flag_type(
                            sge::opengl::convert::to_gl_enum<GL_POINT_SPRITE>()),
                        sge::opengl::state::ffp::misc::point_sprite::config::
                            vertex_shader_size_flag_type(
                                sge::opengl::convert::to_gl_enum<GL_VERTEX_PROGRAM_POINT_SIZE>()),
                        sge::opengl::state::ffp::misc::point_sprite::config::
                            coord_replace_flag_type(
                                sge::opengl::convert::to_gl_enum<GL_COORD_REPLACE>())))
          : sge::opengl::info::extension_supported(
                _info.extensions(), sge::opengl::info::extension{"ARB_point_sprite"})
              ? sge::opengl::state::ffp::misc::point_sprite::optional_config(
                    sge::opengl::state::ffp::misc::point_sprite::config(
                        sge::opengl::state::ffp::misc::point_sprite::config::point_sprite_flag_type(
                            sge::opengl::convert::to_gl_enum<GL_POINT_SPRITE_ARB>()),
                        sge::opengl::state::ffp::misc::point_sprite::config::
                            vertex_shader_size_flag_type(sge::opengl::convert::to_gl_enum<
                                                         GL_VERTEX_PROGRAM_POINT_SIZE_ARB>()),
                        sge::opengl::state::ffp::misc::point_sprite::config::
                            coord_replace_flag_type(
                                sge::opengl::convert::to_gl_enum<GL_COORD_REPLACE_ARB>())))
              : sge::opengl::state::ffp::misc::point_sprite::optional_config())
{
}

sge::opengl::state::ffp::misc::point_sprite::context::~context() = default;

sge::opengl::state::ffp::misc::point_sprite::optional_config const &
sge::opengl::state::ffp::misc::point_sprite::context::config() const
{
  return config_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const sge::opengl::state::ffp::misc::point_sprite::context::static_id(
    sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
