//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/raw_pointer.hpp>
#include <sge/image/color/format_stride.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/opencl/command_queue/map_flags.hpp>
#include <sge/opencl/command_queue/map_flags_to_native.hpp>
#include <sge/opencl/command_queue/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opencl/command_queue/object_ref.hpp>
#include <sge/opencl/command_queue/scoped_planar_mapping.hpp>
#include <sge/opencl/event/sequence.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/impl/event/flatten_sequence.hpp>
#include <sge/opencl/memory_object/rect.hpp>
#include <sge/opencl/memory_object/image/opencl_color_format_to_sge.hpp>
#include <sge/opencl/memory_object/image/planar.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opencl/memory_object/image/planar_ref.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/text.hpp>
#include <fcppt/array/object_impl.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

sge::opencl::command_queue::scoped_planar_mapping::scoped_planar_mapping(
    sge::opencl::command_queue::object_ref const _queue,
    sge::opencl::memory_object::image::planar_ref const _image,
    sge::opencl::command_queue::map_flags const _flags,
    sge::opencl::memory_object::rect const &_rect,
    sge::opencl::event::sequence const &_events)
    : queue_(_queue),
      rect_(_rect),
      sge_image_format_(
          opencl::memory_object::image::opencl_color_format_to_sge(_image.get().image_format())),
      image_(_image.get().impl()),
      ptr_(nullptr),
      pitch_()
{
  cl_int error_code{};

  // We can't use _rect.pos().data() because OpenCL checks if [2] is equal to 0/1
  fcppt::array::object<std::size_t, 3> pos{
      _rect.pos().x(), _rect.pos().y(), fcppt::literal<std::size_t>(0)};
  fcppt::array::object<std::size_t, 3> size{
      _rect.size().w(), _rect.size().h(), fcppt::literal<std::size_t>(1)};

  ptr_ = clEnqueueMapImage(
      _queue.get().impl(),
      image_,
      // Blocking: yes
      CL_TRUE,
      sge::opencl::command_queue::map_flags_to_native(_flags),
      pos.data(),
      size.data(),
      &pitch_,
      // slice pitch
      nullptr,
      static_cast<cl_uint>(_events.size()),
      _events.empty() ? nullptr : sge::opencl::impl::event::flatten_sequence(_events).data(),
      // event
      nullptr,
      &error_code);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clEnqueueMapImage"));
}

void *sge::opencl::command_queue::scoped_planar_mapping::ptr() const { return ptr_; }

std::size_t sge::opencl::command_queue::scoped_planar_mapping::pitch() const { return pitch_; }

sge::image2d::view::object sge::opencl::command_queue::scoped_planar_mapping::view()
{
  return sge::image2d::view::make(
      static_cast<sge::image::raw_pointer>(ptr_),
      fcppt::math::dim::structure_cast<sge::image2d::dim, fcppt::cast::size_fun>(rect_.size()),
      sge_image_format_,
      image2d::pitch(static_cast<image2d::pitch::value_type>(
          pitch_ - rect_.size().w() * sge::image::color::format_stride(sge_image_format_))));
}

sge::opencl::command_queue::scoped_planar_mapping::~scoped_planar_mapping()
{
  if (ptr_ == nullptr)
  {
    return;
  }

  cl_int const error_code =
      clEnqueueUnmapMemObject(queue_.get().impl(), image_, this->ptr(), 0, nullptr, nullptr);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clEnqueueUnmapMemObject"));
}
