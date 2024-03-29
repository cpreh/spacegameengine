//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_DEVICE_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_DEVICE_OBJECT_HPP_INCLUDED

#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <sge/opencl/program/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::device
{

class object
{
public:
  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL cl_device_id impl() const;

  SGE_OPENCL_DETAIL_SYMBOL
  void output_info(std::ostream &) const;

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL bool is_gpu() const;

private:
  friend class sge::opencl::platform::object;
  friend class sge::opencl::context::object;
  friend class sge::opencl::command_queue::object;
  friend class sge::opencl::program::object;

  cl_device_id device_id_;

  explicit object(cl_device_id const &);
};

}

#endif
