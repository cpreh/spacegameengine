//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_TEXTURE_BASIC_BUFFER_IMPL_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_BASIC_BUFFER_IMPL_HPP_INCLUDED

#include <sge/d3d9/lock_flags.hpp>
#include <sge/d3d9/make_pitch.hpp>
#include <sge/d3d9/convert/lock_flags.hpp>
#include <sge/d3d9/texture/basic_buffer.hpp>
#include <sge/d3d9/texture/buffer_size.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/view/make.hpp>
#include <sge/image/view/make_const.hpp>
#include <sge/renderer/basic_lock_box.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/from_mode.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/ignore_dangling_reference.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

template <typename Types>
sge::d3d9::texture::basic_buffer<Types>::basic_buffer(
    d3d_buffer_create_function const &_buffer_create,
    sge::image::color::format const _color_format,
    sge::renderer::resource_flags_field const &_resource_flags)
    : buffer_create_(_buffer_create),
      color_format_(_color_format),
      resource_flags_(_resource_flags),
      size_(sge::d3d9::texture::buffer_size(*buffer_create_())),
      buffer_(),
      locked_dest_()
{
}

template <typename Types>
sge::d3d9::texture::basic_buffer<Types>::~basic_buffer()
{
}

template <typename Types>
typename sge::d3d9::texture::basic_buffer<Types>::view
sge::d3d9::texture::basic_buffer<Types>::lock(
    lock_area const &_area, sge::renderer::lock_mode const _mode)
{
  return this->lock_impl<view>(
      sge::image::view::make<image_tag>, _area, sge::renderer::lock_flags::from_mode(_mode));
}

template <typename Types>
typename sge::d3d9::texture::basic_buffer<Types>::const_view
sge::d3d9::texture::basic_buffer<Types>::lock_c(lock_area const &_area) const
{
  return this->lock_impl<const_view>(
      sge::image::view::make_const<image_tag>, _area, sge::renderer::lock_flags::method::read);
}

template <typename Types>
void sge::d3d9::texture::basic_buffer<Types>::unlock() const
{
  Types::unlock(*fcppt::optional::to_exception(
      this->buffer_,
      [] { return sge::renderer::exception{FCPPT_TEXT("d3d9 texture not locked!")}; }));

  buffer_ = optional_d3d_buffer_unique_ptr();

  locked_dest_ = locked_dest();
}

template <typename Types>
typename sge::d3d9::texture::basic_buffer<Types>::dim
sge::d3d9::texture::basic_buffer<Types>::size() const
{
  return size_;
}

template <typename Types>
sge::image::color::format sge::d3d9::texture::basic_buffer<Types>::format() const
{
  return color_format_;
}

template <typename Types>
template <typename View, typename MakeView>
View sge::d3d9::texture::basic_buffer<Types>::lock_impl(
    MakeView const &_make_view,
    lock_area const &_area,
    sge::renderer::lock_flags::method const _method) const
{
  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_IGNORE_DANGLING_REFERENCE
  d3d_buffer_unique_ptr const &buffer{fcppt::optional::assign(buffer_, buffer_create_())};
  FCPPT_PP_POP_WARNING

  typedef typename Types::lock_dest lock_dest;

  lock_dest const dest_rect(
      // TODO
      _area.size() == this->size() ? lock_dest() : lock_dest(_area));

  sge::d3d9::lock_flags const lock_method(sge::d3d9::convert::lock_flags(_method, resource_flags_));

  typename locked_dest::value_type const dest(Types::lock(*buffer, dest_rect, lock_method));

  locked_dest_ = locked_dest(dest);

  return View(_make_view(
      fcppt::cast::from_void_ptr<sge::image::raw_pointer>(dest.pBits),
      _area.size(),
      color_format_,
      sge::d3d9::make_pitch(dest, _area.size(), color_format_)));
}

#endif
