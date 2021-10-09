//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_BUFFER_BASE_HPP_INCLUDED
#define SGE_OPENGL_BUFFER_BASE_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base_fwd.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id_fwd.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::buffer
{

class base
{
  FCPPT_NONMOVABLE(base);

protected:
  base();

public:
  virtual ~base();

  [[nodiscard]] virtual sge::opengl::buffer::id gen_buffer() = 0;

  virtual void delete_buffer(sge::opengl::buffer::id) = 0;

  virtual void bind_buffer(sge::opengl::buffer::optional_id const &) = 0;

  [[nodiscard]] virtual GLvoid *map_buffer(GLenum flags) = 0;

  [[nodiscard]] virtual GLvoid *
  map_buffer_range(GLbitfield flags, GLintptr first, GLsizeiptr size) = 0;

  [[nodiscard]] virtual bool map_buffer_range_supported() const = 0;

  virtual void unmap_buffer() = 0;

  virtual void buffer_data(GLsizeiptr size, GLvoid const *data, GLenum flags) = 0;

  virtual void buffer_sub_data(GLintptr first, GLsizeiptr size, GLvoid const *data) = 0;

  [[nodiscard]] virtual GLvoid *buffer_offset(GLintptr offset) const = 0;

  [[nodiscard]] virtual bool native() const = 0;
};

}

#endif
