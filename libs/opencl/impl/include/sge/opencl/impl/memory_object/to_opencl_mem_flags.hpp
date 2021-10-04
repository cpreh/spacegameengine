//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_IMPL_MEMORY_OBJECT_TO_OPENCL_MEM_FLAGS_HPP_INCLUDED
#define SGE_OPENCL_IMPL_MEMORY_OBJECT_TO_OPENCL_MEM_FLAGS_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>


namespace sge::opencl::impl::memory_object
{

cl_mem_flags
to_opencl_mem_flags(
	sge::opencl::memory_object::flags_field const &
);

}

#endif
