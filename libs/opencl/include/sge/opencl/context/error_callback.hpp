//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_CONTEXT_ERROR_CALLBACK_HPP_INCLUDED
#define SGE_OPENCL_CONTEXT_ERROR_CALLBACK_HPP_INCLUDED

#include <sge/opencl/context/error_callback_type.hpp>
#include <fcppt/function_impl.hpp>


namespace sge
{
namespace opencl
{
namespace context
{

typedef
fcppt::function<
	sge::opencl::context::error_callback_type
>
error_callback;

}
}
}

#endif
