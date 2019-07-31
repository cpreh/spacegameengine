//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_MEMORY_OBJECT_SCOPED_OBJECTS_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_SCOPED_OBJECTS_HPP_INCLUDED

#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/memory_object/base_ref_sequence.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opencl
{
namespace memory_object
{
class scoped_objects
{
FCPPT_NONCOPYABLE(
	scoped_objects);
public:
	SGE_OPENCL_DETAIL_SYMBOL explicit
	scoped_objects(
		command_queue::object &,
		memory_object::base_ref_sequence const &);

	SGE_OPENCL_DETAIL_SYMBOL ~scoped_objects();
private:
	command_queue::object &queue_;
	memory_object::base_ref_sequence const objects_;
};
}
}
}

#endif
