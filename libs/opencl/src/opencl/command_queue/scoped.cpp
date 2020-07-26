//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opencl/command_queue/object.hpp>
#include <sge/opencl/command_queue/object_ref.hpp>
#include <sge/opencl/command_queue/scoped.hpp>


sge::opencl::command_queue::scoped::scoped(
	sge::opencl::command_queue::object_ref const _object
)
:
	object_(
		_object
	)
{
}

sge::opencl::command_queue::scoped::~scoped()
{
	object_.get().finish();
}
