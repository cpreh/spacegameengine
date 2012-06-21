#include <sge/opencl/event/object.hpp>
#include <sge/src/opencl/handle_error.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

sge::opencl::event::object::object()
:
	handle_(),
	handle_retrieved_(
		false)
{
}

cl_event &
sge::opencl::event::object::handle()
{
	handle_retrieved_ =
		true;

	return
		handle_;
}

cl_event const &
sge::opencl::event::object::handle() const
{
	handle_retrieved_ =
		true;

	return
		handle_;
}

sge::opencl::event::object::~object()
{
	if(!handle_retrieved_)
		return;

	sge::opencl::handle_error(
		clReleaseEvent(
			handle_),
		fcppt::string(
			FCPPT_TEXT("clReleaseEvent")));
}
