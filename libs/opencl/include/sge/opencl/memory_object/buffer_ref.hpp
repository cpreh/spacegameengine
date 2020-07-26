//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_MEMORY_OBJECT_BUFFER_REF_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_BUFFER_REF_HPP_INCLUDED

#include <sge/opencl/memory_object/buffer_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace opencl
{
namespace memory_object
{

using
buffer_ref
=
fcppt::reference<
	sge::opencl::memory_object::buffer
>;

}
}
}

#endif
