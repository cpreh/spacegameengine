//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_CONTEXT_ERROR_CALLBACK_TYPE_HPP_INCLUDED
#define SGE_OPENCL_CONTEXT_ERROR_CALLBACK_TYPE_HPP_INCLUDED

#include <sge/opencl/binary_error_data.hpp>
#include <sge/opencl/error_information_string.hpp>


namespace sge::opencl::context
{

using
error_callback_type
=
void (
	sge::opencl::error_information_string const &,
	sge::opencl::binary_error_data const &
);

}

#endif
