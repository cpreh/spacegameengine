//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image/raw_pointer.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/opencl/command_queue/map_flags.hpp>
#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/command_queue/scoped_planar_mapping.hpp>
#include <sge/opencl/event/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opencl/event/sequence.hpp>
#include <sge/opencl/memory_object/rect.hpp>
#include <sge/opencl/memory_object/image/opencl_color_format_to_sge.hpp>
#include <sge/opencl/memory_object/image/planar.hpp>
#include <sge/opencl/memory_object/image/read_planar.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/math/dim/structure_cast.hpp>

void sge::opencl::memory_object::image::read_planar(
    fcppt::reference<sge::opencl::command_queue::object> const _queue,
    sge::opencl::memory_object::image::planar const &_image,
    sge::image2d::view::object const &_view,
    sge::opencl::memory_object::rect const &_rect)
{
  sge::opencl::command_queue::scoped_planar_mapping const scoped_map{
      _queue,
      fcppt::make_ref(const_cast<sge::opencl::memory_object::image::planar &>(_image)),
      sge::opencl::command_queue::map_flags::read,
      _rect,
      sge::opencl::event::sequence()};

  sge::image2d::algorithm::copy_and_convert(
      sge::image2d::view::make_const(
          static_cast<sge::image::raw_pointer>(scoped_map.ptr()),
          fcppt::math::dim::structure_cast<sge::image2d::dim, fcppt::cast::size_fun>(_rect.size()),
          sge::opencl::memory_object::image::opencl_color_format_to_sge(_image.image_format()),
          sge::image2d::pitch(static_cast<sge::image2d::pitch::value_type>(scoped_map.pitch()))),
      _view,
      sge::image::algorithm::may_overlap::yes,
      sge::image::algorithm::uninitialized::yes);
}
