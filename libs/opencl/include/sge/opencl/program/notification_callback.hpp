//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_PROGRAM_NOTIFICATION_CALLBACK_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_NOTIFICATION_CALLBACK_HPP_INCLUDED

#include <sge/opencl/program/notification_callback_type.hpp>
#include <fcppt/function_impl.hpp>

namespace sge::opencl::program
{

using notification_callback = fcppt::function<sge::opencl::program::notification_callback_type>;

}

#endif
