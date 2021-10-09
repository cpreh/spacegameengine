//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_COMMAND_QUEUE_ENQUEUE_KERNEL_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_ENQUEUE_KERNEL_HPP_INCLUDED

#include <sge/opencl/command_queue/global_dim1.hpp>
#include <sge/opencl/command_queue/global_dim2.hpp>
#include <sge/opencl/command_queue/global_dim3.hpp>
#include <sge/opencl/command_queue/local_dim1.hpp>
#include <sge/opencl/command_queue/local_dim2.hpp>
#include <sge/opencl/command_queue/local_dim3.hpp>
#include <sge/opencl/command_queue/object_ref.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/event/object_unique_ptr.hpp>
#include <sge/opencl/event/sequence.hpp>
#include <sge/opencl/kernel/object_ref.hpp>

namespace sge::opencl::command_queue
{

SGE_OPENCL_DETAIL_SYMBOL
sge::opencl::event::object_unique_ptr enqueue_kernel(
    sge::opencl::command_queue::object_ref,
    sge::opencl::kernel::object_ref,
    sge::opencl::command_queue::global_dim1 const &,
    sge::opencl::command_queue::local_dim1 const &,
    sge::opencl::event::sequence const &);

SGE_OPENCL_DETAIL_SYMBOL
sge::opencl::event::object_unique_ptr enqueue_kernel(
    sge::opencl::command_queue::object_ref,
    sge::opencl::kernel::object_ref,
    sge::opencl::command_queue::global_dim2 const &,
    sge::opencl::command_queue::local_dim2 const &,
    sge::opencl::event::sequence const &);

SGE_OPENCL_DETAIL_SYMBOL
sge::opencl::event::object_unique_ptr enqueue_kernel(
    sge::opencl::command_queue::object_ref,
    sge::opencl::kernel::object_ref,
    sge::opencl::command_queue::global_dim3 const &,
    sge::opencl::command_queue::local_dim3 const &,
    sge::opencl::event::sequence const &);

SGE_OPENCL_DETAIL_SYMBOL
sge::opencl::event::object_unique_ptr enqueue_kernel(
    sge::opencl::command_queue::object_ref,
    sge::opencl::kernel::object_ref,
    sge::opencl::command_queue::global_dim1 const &,
    sge::opencl::event::sequence const &);

SGE_OPENCL_DETAIL_SYMBOL
sge::opencl::event::object_unique_ptr enqueue_kernel(
    sge::opencl::command_queue::object_ref,
    sge::opencl::kernel::object_ref,
    sge::opencl::command_queue::global_dim2 const &,
    sge::opencl::event::sequence const &);

SGE_OPENCL_DETAIL_SYMBOL
sge::opencl::event::object_unique_ptr enqueue_kernel(
    sge::opencl::command_queue::object_ref,
    sge::opencl::kernel::object_ref,
    sge::opencl::command_queue::global_dim3 const &,
    sge::opencl::event::sequence const &);

}

#endif
