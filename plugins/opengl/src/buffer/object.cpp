//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/ext.hpp>
#include <sge/opengl/buffer/base.hpp> // IWYU pragma: keep
#include <sge/opengl/buffer/base_ref.hpp>
#include <sge/opengl/buffer/count.hpp>
#include <sge/opengl/buffer/first.hpp>
#include <sge/opengl/buffer/first_pos.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/normal_lock_method.hpp>
#include <sge/opengl/buffer/object.hpp>
#include <sge/opengl/buffer/optional_id.hpp>
#include <sge/opengl/buffer/range_lock_method.hpp>
#include <sge/opengl/buffer/size.hpp>
#include <sge/opengl/buffer/stride.hpp>
#include <sge/opengl/convert/resource_flags.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/resource_flags.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/read.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/object_impl.hpp> // IWYU pragma: keep
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::opengl::buffer::object::object(
    sge::opengl::buffer::base_ref const _base,
    sge::opengl::buffer::count const _size,
    sge::opengl::buffer::stride const _stride,
    sge::renderer::resource_flags_field const &_flags,
    const_pointer const _src)
    : base_{_base},
      size_{_size.get()},
      stride_{_stride.get()},
      flags_{_flags},
      dest_{nullptr},
      holder_{this->base_},
      lock_offset_{0},
      lock_size_{0}
{
  size_type const new_size{this->size() * this->stride()};

  if (new_size == 0)
  {
    throw sge::renderer::exception(FCPPT_TEXT("ogl_buffer: cannot create an empty buffer!"));
  }

  this->bind();

  this->base_.get().buffer_data(
      sge::opengl::buffer::size{fcppt::cast::size<GLsizeiptr>(fcppt::cast::to_signed(new_size))},
      _src,
      sge::opengl::convert::resource_flags(this->flags()));
}

sge::opengl::buffer::object::~object()
{
  if (this->dest_ != nullptr)
  {
    this->do_unlock();
  }

  this->unbind();
}

void sge::opengl::buffer::object::lock(
    lock_flag_type const &_lockflags, optional_first_pos const _first, optional_count const _count)
{
  if (this->dest_ != nullptr)
  {
    throw sge::renderer::exception(
        FCPPT_TEXT("ogl_buffer::lock(): you have to unlock before locking!"));
  }

  if (sge::renderer::lock_flags::read(_lockflags) &&
      !(this->flags() & sge::renderer::resource_flags::readable))
  {
    throw sge::renderer::exception(
        FCPPT_TEXT("ogl_buffer: Cannot lock a writeonly buffer for reading!"));
  }

  sge::opengl::buffer::first_pos const real_first{
      fcppt::optional::from(_first, fcppt::const_(first_pos{0U}))};

  sge::opengl::buffer::count const real_count{
      fcppt::optional::from(_count, fcppt::const_(count{this->size() - real_first.get()}))};

  if (real_first.get() + real_count.get() > this->size())
  {
    throw sge::renderer::exception{FCPPT_TEXT("ogl_buffer::lock(): first + count > size()")};
  }

  this->bind();

  if (real_count.get() < this->size() && this->base_.get().map_buffer_range_supported())
  {
    this->dest_ = fcppt::cast::from_void_ptr<pointer>(this->base_.get().map_buffer_range(
        sge::opengl::buffer::range_lock_method(_lockflags),
        sge::opengl::buffer::first{
            fcppt::cast::size<GLintptr>(fcppt::cast::to_signed(real_first.get() * this->stride()))},
        sge::opengl::buffer::size{fcppt::cast::size<GLsizeiptr>(
            fcppt::cast::to_signed(real_count.get() * this->stride()))}));

    this->lock_offset_ = 0;
  }
  else
  {
    this->dest_ = fcppt::cast::from_void_ptr<pointer>(
        this->base_.get().map_buffer(sge::opengl::buffer::normal_lock_method(_lockflags)));

    this->lock_offset_ = real_first.get() * this->stride();
  }

  this->lock_size_ = real_count.get() * this->stride();
}

void sge::opengl::buffer::object::unlock()
{
  if (this->dest_ == nullptr)
  {
    throw sge::renderer::exception(
        FCPPT_TEXT("ogl_buffer::unlock(), buffer is not locked! cannot unlock!"));
  }

  this->do_unlock();
}

void sge::opengl::buffer::object::sub_data(
    const_pointer const _data,
    sge::opengl::buffer::first_pos const _first,
    sge::opengl::buffer::count const _count)
{
  if (_first.get() + _count.get() > this->size())
  {
    throw sge::renderer::exception{
        FCPPT_TEXT("ogl_buffer::sub_data(), first + count out of range!")};
  }

  if (this->dest_ != nullptr)
  {
    throw sge::renderer::exception(
        FCPPT_TEXT("ogl_buffer::sub_data(), buffer must not be locked!"));
  }

  this->bind();

  this->base_.get().buffer_sub_data(
      sge::opengl::buffer::first{
          fcppt::cast::size<GLintptr>(fcppt::cast::to_signed(_first.get() * this->stride()))},
      sge::opengl::buffer::size{
          fcppt::cast::size<GLsizeiptr>(fcppt::cast::to_signed(_count.get() * this->stride()))},
      _data);
}

sge::opengl::buffer::object::size_type sge::opengl::buffer::object::size() const
{
  return this->size_;
}

sge::opengl::buffer::object::size_type sge::opengl::buffer::object::stride() const
{
  return this->stride_;
}

sge::renderer::resource_flags_field const &sge::opengl::buffer::object::flags() const
{
  return this->flags_;
}

sge::opengl::buffer::object::pointer sge::opengl::buffer::object::data()
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

  if (this->dest_ == nullptr)
  {
    throw sge::renderer::exception{
        FCPPT_TEXT("ogl_buffer used but the buffer has not been locked!")};
  }

  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  return this->dest_ + this->lock_offset_;

FCPPT_PP_POP_WARNING
}

sge::opengl::buffer::object::const_pointer sge::opengl::buffer::object::data() const
{
  return
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
      const_cast<const_pointer>(
          // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
          const_cast<sge::opengl::buffer::object &>(*this).data());
}

sge::opengl::buffer::object::size_type sge::opengl::buffer::object::lock_size() const
{
  return this->lock_size_;
}

void sge::opengl::buffer::object::unbind() { this->bind_id(sge::opengl::buffer::optional_id{}); }

void sge::opengl::buffer::object::bind() const
{
  this->bind_id(sge::opengl::buffer::optional_id{this->id()});
}

sge::opengl::buffer::object::pointer
sge::opengl::buffer::object::buffer_offset(sge::opengl::buffer::first_pos const _sz) const
{
  if (this->dest_ != nullptr)
  {
    throw sge::renderer::exception(
        FCPPT_TEXT("ogl_buffer::buffer_offset used but the buffer has been locked!"));
  }

  this->bind();

  return fcppt::cast::from_void_ptr<pointer>(base_.get().buffer_offset(sge::opengl::buffer::first{
      fcppt::cast::size<GLintptr>(fcppt::cast::to_signed(_sz.get() * this->stride()))}));
}

sge::opengl::buffer::object::pointer sge::opengl::buffer::object::raw_buffer() const
{
  return this->buffer_offset(first_pos{0U});
}

sge::opengl::buffer::id sge::opengl::buffer::object::id() const { return this->holder_.id(); }

bool sge::opengl::buffer::object::native() const { return this->base_.get().native(); }

void sge::opengl::buffer::object::bind_id(sge::opengl::buffer::optional_id const &_id) const
{
  this->base_.get().bind_buffer(_id);
}

void sge::opengl::buffer::object::do_unlock()
{
  this->bind();

  this->base_.get().unmap_buffer();

  this->dest_ = nullptr;

  this->lock_offset_ = 0;

  this->lock_size_ = 0;
}
