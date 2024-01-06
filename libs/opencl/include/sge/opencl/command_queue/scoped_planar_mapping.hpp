//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_COMMAND_QUEUE_SCOPED_PLANAR_MAPPING_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_SCOPED_PLANAR_MAPPING_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/opencl/command_queue/map_flags_fwd.hpp>
#include <sge/opencl/command_queue/object_ref.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/event/sequence.hpp>
#include <sge/opencl/memory_object/rect.hpp>
#include <sge/opencl/memory_object/image/planar_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::command_queue
{
class scoped_planar_mapping
{
  FCPPT_NONMOVABLE(scoped_planar_mapping);

public:
  SGE_OPENCL_DETAIL_SYMBOL
  scoped_planar_mapping(
      sge::opencl::command_queue::object_ref,
      sge::opencl::memory_object::image::planar_ref,
      sge::opencl::command_queue::map_flags,
      sge::opencl::memory_object::rect const &,
      sge::opencl::event::sequence const &);

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL void *ptr() const;

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL std::size_t pitch() const;

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::image2d::view::object view();

  SGE_OPENCL_DETAIL_SYMBOL
  ~scoped_planar_mapping();

private:
  sge::opencl::command_queue::object_ref const queue_;
  sge::opencl::memory_object::rect rect_;
  sge::image::color::format sge_image_format_;
  cl_mem image_;
  void *ptr_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
  std::size_t pitch_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
};
}

#endif
