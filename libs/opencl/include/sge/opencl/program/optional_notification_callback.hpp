//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_PROGRAM_OPTIONAL_NOTIFICATION_CALLBACK_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_OPTIONAL_NOTIFICATION_CALLBACK_HPP_INCLUDED

#include <sge/opencl/program/notification_callback.hpp>
#include <fcppt/optional/object.hpp>


namespace sge::opencl::program
{

using
optional_notification_callback
=
fcppt::optional::object<
	sge::opencl::program::notification_callback
>;

}

#endif
