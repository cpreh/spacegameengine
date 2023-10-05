//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_IMPL_HANDLE_ERROR_HPP_INCLUDED
#define SGE_OPENCL_IMPL_HANDLE_ERROR_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl_platform.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::impl
{

void handle_error(cl_int, fcppt::string const &);

}

#endif
