//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_MEMORY_OBJECT_FLAGS_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_FLAGS_HPP_INCLUDED

#include <sge/opencl/memory_object/flags_fwd.hpp>


namespace sge
{
namespace opencl
{
namespace memory_object
{

enum class flags
{
	read,
	write,
	alloc_host_ptr,
	fcppt_maximum = alloc_host_ptr
};

}
}
}

#endif
