//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/event/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opencl/event/object_unique_ptr.hpp>
#include <sge/opencl/event/sequence.hpp>
#include <sge/opencl/impl/event/flatten_sequence.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <vector>
#include <fcppt/config/external_end.hpp>

std::vector<cl_event>
sge::opencl::impl::event::flatten_sequence(sge::opencl::event::sequence const &_event_sequence)
{
  return fcppt::algorithm::map<std::vector<cl_event>>(
      _event_sequence,
      [](sge::opencl::event::object_unique_ptr const &_ptr) { return _ptr->handle(); });
}
