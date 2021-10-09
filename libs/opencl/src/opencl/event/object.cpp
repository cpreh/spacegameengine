//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/event/object.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

sge::opencl::event::object::object() : handle_(), handle_retrieved_(false) {}

cl_event &sge::opencl::event::object::handle()
{
  handle_retrieved_ = true;

  return handle_;
}

cl_event const &sge::opencl::event::object::handle() const
{
  handle_retrieved_ = true;

  return handle_;
}

sge::opencl::event::object::~object()
{
  if (!handle_retrieved_)
  {
    return;
  }

  sge::opencl::impl::handle_error(
      clReleaseEvent(handle_), fcppt::string(FCPPT_TEXT("clReleaseEvent")));
}
