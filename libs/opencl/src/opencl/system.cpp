//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/system.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/platform/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/buffer/object.hpp>

sge::opencl::system::system()
    : // TODO(philipp): Direct initialization
      platforms_()
{
  cl_uint number_of_platforms{};

  // First, query the total number of platforms
  cl_int error_code = clGetPlatformIDs(
      // maximum number of entries
      0,
      // pointer to the entries array
      nullptr,
      &number_of_platforms);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clGetplatformIDs"));

  if (number_of_platforms == 0)
  {
    return;
  }

  using platform_id_sequence = fcppt::container::buffer::object<cl_platform_id>;

  platform_id_sequence platform_ids(
      static_cast<platform_id_sequence::size_type>(number_of_platforms));

  // First, query the total number of platforms
  error_code = clGetPlatformIDs(
      number_of_platforms,
      platform_ids.write_data(),
      // pointer to the number of platforms
      nullptr);

  platform_ids.written(platform_ids.write_size());

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clGetplatformIDs"));

  // TODO(philipp): map
  for (auto const &platform : platform_ids)
  {
    platforms_.push_back(opencl::platform::object(platform));
  }
}

sge::opencl::platform::object_sequence &sge::opencl::system::platforms() { return platforms_; }

sge::opencl::platform::object_sequence const &sge::opencl::system::platforms() const
{
  return platforms_;
}

sge::opencl::system::~system() = default;
