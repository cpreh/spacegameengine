//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_EVENT_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_EVENT_OBJECT_HPP_INCLUDED

#include <sge/opencl/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::event
{

class object
{
  FCPPT_NONMOVABLE(object);

public:
  SGE_OPENCL_DETAIL_SYMBOL
  object();

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL cl_event &handle();

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL cl_event const &handle() const;

  SGE_OPENCL_DETAIL_SYMBOL
  ~object();

private:
  cl_event handle_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
  mutable bool handle_retrieved_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
};

}

#endif
