//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_COMMAND_QUEUE_SCOPED_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_SCOPED_HPP_INCLUDED

#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opencl
{
namespace command_queue
{
class scoped
{
FCPPT_NONCOPYABLE(
	scoped);
public:
	SGE_OPENCL_DETAIL_SYMBOL explicit
	scoped(
		command_queue::object &);

	SGE_OPENCL_DETAIL_SYMBOL ~scoped();
private:
	command_queue::object &object_;
};
}
}
}

#endif
