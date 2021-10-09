//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/impl/vf/dynamic/element_converter.hpp>
#include <sge/renderer/impl/vf/dynamic/lock_interval.hpp>
#include <sge/renderer/impl/vf/dynamic/unlock.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>

sge::renderer::impl::vf::dynamic::element_converter::element_converter(
    original_format const _original_format,
    backend_format const _backend_format,
    sge::renderer::vf::dynamic::stride const _stride,
    sge::renderer::vf::dynamic::offset const _offset)
    : original_format_(_original_format),
      backend_format_(_backend_format),
      stride_(_stride),
      offset_(_offset)
{
  if (sge::image::color::format_stride(original_format_.get()) !=
      sge::image::color::format_stride(backend_format_.get()))
  {
    throw sge::renderer::exception{
        FCPPT_TEXT("vf::dynamic::element_converter: Cannot handle different format strides!")};
  }
}

void sge::renderer::impl::vf::dynamic::element_converter::convert(
    sge::renderer::impl::vf::dynamic::lock_interval const &_interval,
    sge::renderer::raw_pointer const _data,
    sge::renderer::vertex::first const _pos,
    sge::renderer::impl::vf::dynamic::unlock const _unlock) const
{
  if (original_format_.get() == backend_format_.get())
  {
    return;
  }

  // pos refers to the beginning of the lock
  if (_interval.lower() < _pos.get())
  {
    throw sge::renderer::exception{
        FCPPT_TEXT("vf::dynamic::element_converter: Lock out of range!")};
  }

  sge::renderer::raw_pointer const begin(
      _data + (_interval.lower() - _pos.get()) * stride_.get() + offset_.get());

  sge::image2d::dim const dim(1U, _interval.upper() - _interval.lower());

  sge::image2d::pitch const pitch{fcppt::cast::to_signed(
      stride_.get() - sge::image::color::format_stride(original_format_.get()))};

  sge::image2d::algorithm::copy_and_convert(
      sge::image2d::view::make_const(
          begin, dim, _unlock.get() ? original_format_.get() : backend_format_.get(), pitch),
      sge::image2d::view::make(
          begin, dim, _unlock.get() ? backend_format_.get() : original_format_.get(), pitch),
      sge::image::algorithm::may_overlap::yes,
      sge::image::algorithm::uninitialized::no);
}
