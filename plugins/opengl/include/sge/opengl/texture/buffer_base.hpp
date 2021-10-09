//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_BUFFER_BASE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BUFFER_BASE_HPP_INCLUDED

#include <sge/opengl/texture/buffer_base_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::texture
{

class buffer_base
{
  FCPPT_NONMOVABLE(buffer_base);

protected:
  buffer_base(
      sge::opengl::texture::buffer_type,
      sge::opengl::texture::id,
      sge::renderer::texture::mipmap::level,
      sge::opengl::texture::is_render_target);

public:
  virtual ~buffer_base();

  [[nodiscard]] sge::opengl::texture::buffer_type buffer_type() const;

  [[nodiscard]] sge::opengl::texture::id id() const;

  [[nodiscard]] sge::renderer::texture::mipmap::level level() const;

  [[nodiscard]] sge::opengl::texture::is_render_target is_render_target() const;

private:
  sge::opengl::texture::buffer_type const buffer_type_;

  sge::opengl::texture::id const id_;

  sge::renderer::texture::mipmap::level const level_;

  sge::opengl::texture::is_render_target const is_render_target_;
};

}

#endif
