#ifndef SGE_OPENCL_HANDLE_ERROR_HPP_INCLUDED
#define SGE_OPENCL_HANDLE_ERROR_HPP_INCLUDED

#include <CL/cl.h>
#include <fcppt/string.hpp>

namespace sge
{
namespace opencl
{
void
handle_error(
	cl_int,
	fcppt::string const &);
}
}

#endif
