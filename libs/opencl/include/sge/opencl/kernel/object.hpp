//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_KERNEL_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_KERNEL_OBJECT_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/device/object_fwd.hpp>
#include <sge/opencl/kernel/argument_index.hpp>
#include <sge/opencl/kernel/local_buffer_fwd.hpp>
#include <sge/opencl/kernel/name.hpp>
#include <sge/opencl/kernel/numeric_type.hpp>
#include <sge/opencl/memory_object/base_fwd.hpp>
#include <sge/opencl/memory_object/byte_size.hpp>
#include <sge/opencl/program/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opencl
{
namespace kernel
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_DETAIL_SYMBOL explicit
	object(
		program::object &,
		kernel::name const &);

	SGE_OPENCL_DETAIL_SYMBOL void
	argument(
		kernel::argument_index const &,
		memory_object::base &);

	SGE_OPENCL_DETAIL_SYMBOL void
	argument(
		kernel::argument_index const &,
		kernel::numeric_type const &);

	SGE_OPENCL_DETAIL_SYMBOL void
	argument(
		kernel::argument_index const &,
		unsigned char const *,
		memory_object::byte_size const &);

	SGE_OPENCL_DETAIL_SYMBOL void
	argument(
		kernel::argument_index const &,
		kernel::local_buffer const &);

	SGE_OPENCL_DETAIL_SYMBOL std::size_t
	work_group_size(
		opencl::device::object &) const;

	SGE_OPENCL_DETAIL_SYMBOL kernel::name::value_type
	name() const;

	SGE_OPENCL_DETAIL_SYMBOL cl_kernel
	impl();

	SGE_OPENCL_DETAIL_SYMBOL ~object();
private:
	kernel::name::value_type name_;
	cl_kernel kernel_;
	cl_uint argument_count_;
};
}
}
}

#endif
