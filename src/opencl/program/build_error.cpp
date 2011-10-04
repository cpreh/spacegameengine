#include <sge/opencl/program/build_error.hpp>
#include <fcppt/text.hpp>

sge::opencl::program::build_error::build_error(
	fcppt::string const &_message)
:
	sge::exception(
		FCPPT_TEXT("Error building OpenCL program: ")+_message),
	message_(
		_message)
{
}

fcppt::string const &
sge::opencl::program::build_error::message() const
{
	return message_;
}

sge::opencl::program::build_error::~build_error() throw()
{
}
