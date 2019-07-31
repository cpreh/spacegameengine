//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_COMMAND_QUEUE_EXECUTION_MODE_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_EXECUTION_MODE_HPP_INCLUDED

#include <sge/opencl/command_queue/execution_mode_fwd.hpp>


namespace sge
{
namespace opencl
{
namespace command_queue
{

enum class execution_mode
{
	in_order,
	out_of_order
};

}
}
}

#endif
