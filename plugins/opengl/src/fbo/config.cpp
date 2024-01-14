//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/config.hpp>
#include <sge/opengl/fbo/error_string_map.hpp>
#include <sge/opengl/fbo/optional_attachment_type.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/maybe_void.hpp>

sge::opengl::fbo::config::config(
    gl_gen_framebuffers _gen_framebuffers,
    gl_delete_framebuffers _delete_framebuffers,
    gl_bind_framebuffer _bind_framebuffer,
    gl_framebuffer_texture_2d _framebuffer_texture_2d,
    gl_check_framebuffer_status _check_framebuffer_status,
    gl_gen_renderbuffers _gen_renderbuffers,
    gl_delete_renderbuffers _delete_renderbuffers,
    gl_bind_renderbuffer _bind_renderbuffer,
    gl_renderbuffer_storage _renderbuffer_storage,
    gl_framebuffer_renderbuffer _framebuffer_renderbuffer,
    target_type const _framebuffer_target,
    color_attachment_type const _color_attachment,
    fbo_complete_type const _fbo_complete,
    fbo_undefined_type const _fbo_undefined,
    fbo_incomplete_attachment_type const _fbo_incomplete_attachment,
    fbo_incomplete_missing_attachment_type const _fbo_incomplete_missing_attachment,
    fbo_incomplete_draw_buffer_type const _fbo_incomplete_draw_buffer,
    fbo_incomplete_read_buffer_type const _fbo_incomplete_read_buffer,
    fbo_unsupported_type const _fbo_unsupported,
    fbo_incomplete_multisample_type const _fbo_incomplete_multisample,
    fbo_incomplete_layer_targets_type const _fbo_incomplete_layer_targets,
    renderbuffer_target_type const _renderbuffer_target,
    depth_attachment_type const _depth_attachment,
    depth_stencil_attachment_type const _depth_stencil_attachment)
    : gen_framebuffers_{_gen_framebuffers},
      delete_framebuffers_{_delete_framebuffers},
      bind_framebuffer_{_bind_framebuffer},
      framebuffer_texture_2d_{_framebuffer_texture_2d},
      check_framebuffer_status_{_check_framebuffer_status},
      gen_renderbuffers_{_gen_renderbuffers},
      delete_renderbuffers_{_delete_renderbuffers},
      bind_renderbuffer_{_bind_renderbuffer},
      renderbuffer_storage_{_renderbuffer_storage},
      framebuffer_renderbuffer_{_framebuffer_renderbuffer},
      framebuffer_target_{_framebuffer_target.get()},
      color_attachment_{_color_attachment.get()},
      framebuffer_complete_{_fbo_complete.get()},
      error_strings_{
          sge::opengl::fbo::error_string_map::value_type{
              _fbo_incomplete_attachment.get(), FCPPT_TEXT("incomplete attachment")},
          sge::opengl::fbo::error_string_map::value_type{
              _fbo_incomplete_missing_attachment.get(), FCPPT_TEXT("incomplete missing attachment")},
          sge::opengl::fbo::error_string_map::value_type{
              _fbo_incomplete_draw_buffer.get(), FCPPT_TEXT("incomplete draw buffer")},
          sge::opengl::fbo::error_string_map::value_type{
              _fbo_incomplete_read_buffer.get(), FCPPT_TEXT("incomplete read buffer")},
          sge::opengl::fbo::error_string_map::value_type{
              _fbo_unsupported.get(), FCPPT_TEXT("unsupported")},
          sge::opengl::fbo::error_string_map::value_type{
              _fbo_incomplete_multisample.get(), FCPPT_TEXT("incomplete multisample")},
          sge::opengl::fbo::error_string_map::value_type{
              _fbo_incomplete_layer_targets.get(), FCPPT_TEXT("incomplete layer targets")}},
      renderbuffer_target_{_renderbuffer_target.get()},
      depth_attachment_{_depth_attachment.get()},
      depth_stencil_attachment_{_depth_stencil_attachment.get()}
{
  fcppt::optional::maybe_void(
      _fbo_undefined.get(),
      [this](GLenum const _value)
      {
        error_strings_.insert(
            sge::opengl::fbo::error_string_map::value_type{_value, FCPPT_TEXT("undefined")});
      });
}

sge::opengl::fbo::config::gl_gen_framebuffers sge::opengl::fbo::config::gen_framebuffers() const
{
  return gen_framebuffers_;
}

sge::opengl::fbo::config::gl_delete_framebuffers
sge::opengl::fbo::config::delete_framebuffers() const
{
  return delete_framebuffers_;
}

sge::opengl::fbo::config::gl_bind_framebuffer sge::opengl::fbo::config::bind_framebuffer() const
{
  return bind_framebuffer_;
}

sge::opengl::fbo::config::gl_framebuffer_texture_2d
sge::opengl::fbo::config::framebuffer_texture_2d() const
{
  return framebuffer_texture_2d_;
}

sge::opengl::fbo::config::gl_check_framebuffer_status
sge::opengl::fbo::config::check_framebuffer_status() const
{
  return check_framebuffer_status_;
}

sge::opengl::fbo::config::gl_gen_renderbuffers sge::opengl::fbo::config::gen_renderbuffers() const
{
  return gen_renderbuffers_;
}

sge::opengl::fbo::config::gl_delete_renderbuffers
sge::opengl::fbo::config::delete_renderbuffers() const
{
  return delete_renderbuffers_;
}

sge::opengl::fbo::config::gl_bind_renderbuffer sge::opengl::fbo::config::bind_renderbuffer() const
{
  return bind_renderbuffer_;
}

sge::opengl::fbo::config::gl_renderbuffer_storage
sge::opengl::fbo::config::renderbuffer_storage() const
{
  return renderbuffer_storage_;
}

sge::opengl::fbo::config::gl_framebuffer_renderbuffer
sge::opengl::fbo::config::framebuffer_renderbuffer() const
{
  return framebuffer_renderbuffer_;
}

GLenum sge::opengl::fbo::config::framebuffer_target() const { return framebuffer_target_; }

sge::opengl::fbo::attachment_type sge::opengl::fbo::config::color_attachment() const
{
  return color_attachment_;
}

GLenum sge::opengl::fbo::config::framebuffer_complete() const { return framebuffer_complete_; }

sge::opengl::fbo::error_string_map const &sge::opengl::fbo::config::error_strings() const
{
  return error_strings_;
}

GLenum sge::opengl::fbo::config::renderbuffer_target() const { return renderbuffer_target_; }

sge::opengl::fbo::attachment_type sge::opengl::fbo::config::depth_attachment() const
{
  return depth_attachment_;
}

sge::opengl::fbo::optional_attachment_type
sge::opengl::fbo::config::depth_stencil_attachment() const
{
  return depth_stencil_attachment_;
}
