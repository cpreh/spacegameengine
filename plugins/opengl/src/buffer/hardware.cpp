//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/const_hardware_config_ref.hpp>
#include <sge/opengl/buffer/first.hpp>
#include <sge/opengl/buffer/hardware.hpp>
#include <sge/opengl/buffer/hardware_config.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id.hpp>
#include <sge/opengl/buffer/size.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/const.hpp>
#include <fcppt/strong_typedef_comparison.hpp> // IWYU pragma: keep
#include <fcppt/text.hpp>
#include <fcppt/cast/to_void_ptr.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/to_exception.hpp>

sge::opengl::buffer::hardware::hardware(
    sge::opengl::buffer::type const _type,
    sge::opengl::buffer::const_hardware_config_ref const _config)
    : sge::opengl::buffer::base{}, type_{_type}, config_{_config}, bound_buffer_{}
{
}

sge::opengl::buffer::hardware::~hardware() = default;

sge::opengl::buffer::id sge::opengl::buffer::hardware::gen_buffer()
{
  GLuint new_id{};

  sge::opengl::call_fun_ref(this->config_.get().gen_buffers(), 1, &new_id);

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glGenBuffers failed"), sge::renderer::exception)

  return sge::opengl::buffer::id{new_id};
}

void sge::opengl::buffer::hardware::delete_buffer(sge::opengl::buffer::id const _id)
{
  sge::opengl::call_fun_ref(this->config_.get().delete_buffers(), 1, &_id.get());

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glDeleteBuffers failed"), sge::renderer::exception)
}

void sge::opengl::buffer::hardware::bind_buffer(sge::opengl::buffer::optional_id const &_id)
{
  if (_id == this->bound_buffer_)
  {
    return;
  }

  this->bound_buffer_ = _id;

  sge::opengl::buffer::id const id{
      fcppt::optional::from(_id, fcppt::const_(sge::opengl::buffer::id(0U)))};

  sge::opengl::call_fun_ref(this->config_.get().bind_buffer(), this->type_.get(), id.get());

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glBindBuffer failed"), sge::renderer::exception)
}

GLvoid *sge::opengl::buffer::hardware::map_buffer(GLenum const _flags)
{
  GLvoid *const ret{fcppt::cast::to_void_ptr(
      sge::opengl::call_fun_ref(this->config_.get().map_buffer(), this->type_.get(), _flags))};

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glMapBuffer failed"), sge::renderer::exception)

  return ret;
}

GLvoid *sge::opengl::buffer::hardware::map_buffer_range(
    GLbitfield const _flags,
    sge::opengl::buffer::first const _first,
    sge::opengl::buffer::size const _size)
{
  GLvoid *const ret{sge::opengl::call_fun_ref(
      fcppt::optional::to_exception(
          this->config_.get().map_buffer_range(),
          [] { return sge::renderer::exception{FCPPT_TEXT("GL map buffer range not set!")}; }),
      this->type_.get(),
      _first.get(),
      _size.get(),
      _flags)};

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glMapBufferRange failed"), sge::renderer::exception)

  return ret;
}

bool sge::opengl::buffer::hardware::map_buffer_range_supported() const
{
  return this->config_.get().map_buffer_range().has_value();
}

void sge::opengl::buffer::hardware::unmap_buffer()
{
  sge::opengl::call_fun_ref(this->config_.get().unmap_buffer(), this->type_.get());

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glUnmapBuffer failed"), sge::renderer::exception)
}

void sge::opengl::buffer::hardware::buffer_data(
    sge::opengl::buffer::size const _size, GLvoid const *const _data, GLenum const _flags)
{
  sge::opengl::call_fun_ref(
      this->config_.get().buffer_data(), this->type_.get(), _size.get(), _data, _flags);

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glBufferData failed"), sge::renderer::exception)
}

void sge::opengl::buffer::hardware::buffer_sub_data(
    sge::opengl::buffer::first const _first,
    sge::opengl::buffer::size const _size,
    GLvoid const *const _data)
{
  sge::opengl::call_fun_ref(
      this->config_.get().buffer_sub_data(), this->type_.get(), _first.get(), _size.get(), _data);

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glBufferSubData failed"), sge::renderer::exception)
}

void *sge::opengl::buffer::hardware::buffer_offset(sge::opengl::buffer::first const _offset) const
{
  return
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
      reinterpret_cast<void *>(_offset.get());
}

bool sge::opengl::buffer::hardware::native() const { return true; }
