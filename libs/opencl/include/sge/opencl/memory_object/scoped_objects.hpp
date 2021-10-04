//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_MEMORY_OBJECT_SCOPED_OBJECTS_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_SCOPED_OBJECTS_HPP_INCLUDED

#include <sge/opencl/command_queue/object_ref.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/memory_object/base_ref_sequence.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::opencl::memory_object
{

class scoped_objects
{
	FCPPT_NONMOVABLE(
		scoped_objects
	);
public:
	SGE_OPENCL_DETAIL_SYMBOL
	scoped_objects(
		sge::opencl::command_queue::object_ref,
		sge::opencl::memory_object::base_ref_sequence &&
	);

	SGE_OPENCL_DETAIL_SYMBOL
	~scoped_objects();
private:
	sge::opencl::command_queue::object_ref const queue_;
	sge::opencl::memory_object::base_ref_sequence const objects_;
};

}

#endif
