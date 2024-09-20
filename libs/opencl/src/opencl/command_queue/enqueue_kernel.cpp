//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/exception.hpp>
#include <sge/opencl/size_type.hpp>
#include <sge/opencl/command_queue/enqueue_kernel.hpp>
#include <sge/opencl/command_queue/global_dim1.hpp>
#include <sge/opencl/command_queue/global_dim2.hpp>
#include <sge/opencl/command_queue/global_dim3.hpp>
#include <sge/opencl/command_queue/local_dim1.hpp>
#include <sge/opencl/command_queue/local_dim2.hpp>
#include <sge/opencl/command_queue/local_dim3.hpp>
#include <sge/opencl/command_queue/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opencl/command_queue/object_ref.hpp>
#include <sge/opencl/event/object.hpp>
#include <sge/opencl/event/object_unique_ptr.hpp>
#include <sge/opencl/event/sequence.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/impl/event/flatten_sequence.hpp>
#include <sge/opencl/kernel/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opencl/kernel/object_ref.hpp>
#include <fcppt/const.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/contents.hpp>
#include <fcppt/math/dim/output.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/math/dim/static.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <fcppt/config/external_end.hpp>

namespace
{

template <fcppt::math::size_type N>
sge::opencl::event::object_unique_ptr enqueue_kernel_internal(
    sge::opencl::command_queue::object_ref const _command_queue,
    sge::opencl::kernel::object_ref const _kernel,
    fcppt::math::dim::static_<sge::opencl::size_type, N> const &_global_dim,
    fcppt::optional::object<fcppt::math::dim::static_<sge::opencl::size_type, N>> const &_work_dim,
    sge::opencl::event::sequence const &_events)
{
  using dim_type = fcppt::math::dim::static_<sge::opencl::size_type, N>;

  if (fcppt::math::dim::contents(_global_dim) == 0U ||
      fcppt::optional::maybe(
          _work_dim,
          fcppt::const_(false),
          [](dim_type const &_dim) { return fcppt::math::dim::contents(_dim) == 0U; }))
  {
    throw sge::opencl::exception{
        FCPPT_TEXT("Neither global nor work dimensions can be zero in any component")};
  }

  sge::opencl::event::object_unique_ptr result{
      fcppt::make_unique_ptr<sge::opencl::event::object>()};

  cl_int const error_code{clEnqueueNDRangeKernel(
      _command_queue.get().impl(),
      _kernel.get().impl(),
      fcppt::cast::size<cl_uint>(N),
      nullptr, // global work offset (not implemented in 1.1)
      _global_dim.storage().data(),
      fcppt::optional::maybe(
          _work_dim,
          [] { return typename dim_type::storage_type::const_pointer{nullptr}; },
          [](dim_type const &_dim) { return _dim.storage().data(); }),
      fcppt::cast::size<cl_uint>(_events.size()),
      _events.empty() ? nullptr : sge::opencl::impl::event::flatten_sequence(_events).data(),
      &(result->handle()))};

  if (error_code == CL_INVALID_WORK_GROUP_SIZE)
  {
    throw sge::opencl::exception(
        FCPPT_TEXT("Error enqueuing kernel \"") + fcppt::from_std_string(_kernel.get().name()) +
        FCPPT_TEXT("\": workgroup size invalid. The global dimension is ") +
        fcppt::output_to_fcppt_string(_global_dim) +
        fcppt::optional::maybe(
            _work_dim,
            [] { return fcppt::string{}; },
            [](dim_type const &_dim) {
              return FCPPT_TEXT(", the workgroup dimension is ") +
                     fcppt::output_to_fcppt_string(_dim);
            }));
  }

  sge::opencl::impl::handle_error(error_code, FCPPT_TEXT("clEnqueueNDRangeKernel(work)"));

  return result;
}

template <fcppt::math::size_type N, typename GlobalDim, typename LocalDim>
sge::opencl::event::object_unique_ptr enqueue_kernel_templatized(
    sge::opencl::command_queue::object_ref const _command_queue,
    sge::opencl::kernel::object_ref const _kernel,
    fcppt::strong_typedef<fcppt::math::dim::static_<sge::opencl::size_type, N>, GlobalDim> const
        &_global_dim,
    fcppt::strong_typedef<fcppt::math::dim::static_<sge::opencl::size_type, N>, LocalDim> const
        &_local_dim,
    sge::opencl::event::sequence const &_events)
{
  return enqueue_kernel_internal(
      _command_queue, _kernel, _global_dim.get(), fcppt::optional::make(_local_dim.get()), _events);
}

template <typename GlobalDim>
sge::opencl::event::object_unique_ptr enqueue_kernel_templatized(
    sge::opencl::command_queue::object_ref const _command_queue,
    sge::opencl::kernel::object_ref const _kernel,
    GlobalDim const &_global_dim,
    sge::opencl::event::sequence const &_events)
{
  return enqueue_kernel_internal(
      _command_queue,
      _kernel,
      _global_dim.get(),
      fcppt::optional::object<typename GlobalDim::value_type>(),
      _events);
}

}

sge::opencl::event::object_unique_ptr sge::opencl::command_queue::enqueue_kernel(
    sge::opencl::command_queue::object_ref const _command_queue,
    sge::opencl::kernel::object_ref const _kernel,
    sge::opencl::command_queue::global_dim1 const &_global_dim,
    sge::opencl::command_queue::local_dim1 const &_local_dim,
    sge::opencl::event::sequence const &_events)
{
  return enqueue_kernel_templatized(_command_queue, _kernel, _global_dim, _local_dim, _events);
}

sge::opencl::event::object_unique_ptr sge::opencl::command_queue::enqueue_kernel(
    sge::opencl::command_queue::object_ref const _command_queue,
    sge::opencl::kernel::object_ref const _kernel,
    sge::opencl::command_queue::global_dim2 const &_global_dim,
    sge::opencl::command_queue::local_dim2 const &_local_dim,
    sge::opencl::event::sequence const &_events)
{
  return enqueue_kernel_templatized(_command_queue, _kernel, _global_dim, _local_dim, _events);
}

sge::opencl::event::object_unique_ptr sge::opencl::command_queue::enqueue_kernel(
    sge::opencl::command_queue::object_ref const _command_queue,
    sge::opencl::kernel::object_ref const _kernel,
    sge::opencl::command_queue::global_dim3 const &_global_dim,
    sge::opencl::command_queue::local_dim3 const &_local_dim,
    sge::opencl::event::sequence const &_events)
{
  return enqueue_kernel_templatized(_command_queue, _kernel, _global_dim, _local_dim, _events);
}

sge::opencl::event::object_unique_ptr sge::opencl::command_queue::enqueue_kernel(
    sge::opencl::command_queue::object_ref const _command_queue,
    sge::opencl::kernel::object_ref const _kernel,
    sge::opencl::command_queue::global_dim1 const &_global_dim,
    sge::opencl::event::sequence const &_events)
{
  return enqueue_kernel_templatized(_command_queue, _kernel, _global_dim, _events);
}

sge::opencl::event::object_unique_ptr sge::opencl::command_queue::enqueue_kernel(
    sge::opencl::command_queue::object_ref const _command_queue,
    sge::opencl::kernel::object_ref const _kernel,
    sge::opencl::command_queue::global_dim2 const &_global_dim,
    sge::opencl::event::sequence const &_events)
{
  return enqueue_kernel_templatized(_command_queue, _kernel, _global_dim, _events);
}

sge::opencl::event::object_unique_ptr sge::opencl::command_queue::enqueue_kernel(
    sge::opencl::command_queue::object_ref const _command_queue,
    sge::opencl::kernel::object_ref const _kernel,
    sge::opencl::command_queue::global_dim3 const &_global_dim,
    sge::opencl::event::sequence const &_events)
{
  return enqueue_kernel_templatized(_command_queue, _kernel, _global_dim, _events);
}
