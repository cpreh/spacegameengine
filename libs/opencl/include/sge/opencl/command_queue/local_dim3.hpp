//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_COMMAND_QUEUE_LOCAL_DIM3_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_LOCAL_DIM3_HPP_INCLUDED

#include <sge/opencl/dim3.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace opencl
{
namespace command_queue
{

FCPPT_MAKE_STRONG_TYPEDEF(
	sge::opencl::dim3,
	local_dim3
);

}
}
}

#endif
