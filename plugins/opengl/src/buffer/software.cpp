//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/ext.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id.hpp>
#include <sge/opengl/buffer/software.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/text.hpp>
#include <fcppt/use.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

sge::opengl::buffer::software::software()
    : sge::opengl::buffer::base(), bound_buffer_(), nextid_(0U), buffers_()
{
}

sge::opengl::buffer::software::~software() = default;

sge::opengl::buffer::id sge::opengl::buffer::software::gen_buffer()
{
  buffers_.insert(std::make_pair(nextid_, nullptr));

  return nextid_++;
}

void sge::opengl::buffer::software::delete_buffer(sge::opengl::buffer::id const _id)
{
  buffer_map::iterator const it(fcppt::optional::to_exception(
      fcppt::container::find_opt_iterator(buffers_, _id),
      [] { return sge::renderer::exception{FCPPT_TEXT("delete_buffer(): Buffer not found!")}; }));

  // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
  delete[] it->second;

  buffers_.erase(it);
}

void sge::opengl::buffer::software::bind_buffer(sge::opengl::buffer::optional_id const &_id)
{
  bound_buffer_ = _id;
}

GLvoid *sge::opengl::buffer::software::map_buffer(GLenum)
{
  return this->buffer_object(this->bound_buffer());
}

GLvoid *
sge::opengl::buffer::software::map_buffer_range(GLbitfield, GLintptr const _first, GLsizeiptr)
{
  return this->buffer_object(this->bound_buffer()) + _first;
}

bool sge::opengl::buffer::software::map_buffer_range_supported() const { return true; }

void sge::opengl::buffer::software::unmap_buffer()
{
  // For error checking only
  FCPPT_USE(this->bound_buffer());
}

void sge::opengl::buffer::software::buffer_data(
    GLsizeiptr const _size, void const *const _data, GLenum)
{
  sge::renderer::raw_pointer &buffer(this->buffer_object(this->bound_buffer()));

  // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
  delete[] buffer;

  // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
  buffer = new sge::renderer::raw_value[fcppt::cast::to_unsigned(_size)];

  if (_data != nullptr)
  {
    this->buffer_sub_data(0, _size, _data);
  }
}

void sge::opengl::buffer::software::buffer_sub_data(
    GLintptr const _first, GLsizeiptr const _size, void const *const _data)
{
  if (_data == nullptr)
  {
    throw sge::renderer::exception{FCPPT_TEXT("buffer_sub_data(): data may not be 0!")};
  }

  std::copy_n(
      fcppt::cast::to_char_ptr<sge::renderer::const_raw_pointer>(_data) + _first,
      _size,
      this->buffer_object(this->bound_buffer()));
}

void *sge::opengl::buffer::software::buffer_offset(GLintptr const _offset) const
{
  return
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
      const_cast<sge::renderer::raw_pointer>(this->buffer_object(this->bound_buffer()) + _offset);
}

bool sge::opengl::buffer::software::native() const { return false; }

sge::opengl::buffer::id sge::opengl::buffer::software::bound_buffer() const
{
  return fcppt::optional::to_exception(
      bound_buffer_,
      [] { return sge::renderer::exception{FCPPT_TEXT("bound_buffer(): Buffer not bound!")}; });
}

sge::renderer::raw_pointer &
sge::opengl::buffer::software::buffer_object(sge::opengl::buffer::id const _id)
{
  return fcppt::optional::to_exception(
             fcppt::container::find_opt_mapped(buffers_, _id),
             [] { return sge::renderer::exception{FCPPT_TEXT("buffer_object(): invalid id!")}; })
      .get();
}

sge::renderer::const_raw_pointer
sge::opengl::buffer::software::buffer_object(sge::opengl::buffer::id const _id) const
{
  return
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
      const_cast<sge::opengl::buffer::software &>(*this).buffer_object(_id);
}

FCPPT_PP_POP_WARNING
