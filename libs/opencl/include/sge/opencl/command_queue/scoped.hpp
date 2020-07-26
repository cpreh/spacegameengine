//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_COMMAND_QUEUE_SCOPED_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_SCOPED_HPP_INCLUDED

#include <sge/opencl/command_queue/object_ref.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace opencl
{
namespace command_queue
{

class scoped
{
	FCPPT_NONMOVABLE(
		scoped
	);
public:
	SGE_OPENCL_DETAIL_SYMBOL
	explicit
	scoped(
		sge::opencl::command_queue::object_ref
	);

	SGE_OPENCL_DETAIL_SYMBOL
	~scoped();
private:
	sge::opencl::command_queue::object_ref const object_;
};

}
}
}

#endif
