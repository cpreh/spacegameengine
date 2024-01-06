//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_KERNEL_NUMERIC_TYPE_HPP_INCLUDED
#define SGE_OPENCL_KERNEL_NUMERIC_TYPE_HPP_INCLUDED

#include <fcppt/mpl/list/object.hpp>
#include <fcppt/mpl/list/unique.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/from_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl_platform.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::kernel
{

FCPPT_PP_PUSH_WARNING
// Alignment does not matter here
FCPPT_PP_DISABLE_GCC_WARNING(-Wignored-attributes)

using numeric_type = fcppt::variant::from_list<fcppt::mpl::list::unique<fcppt::mpl::list::object<
    cl_char,
    cl_uchar,
    cl_short,
    cl_ushort,
    cl_int,
    cl_uint,
    cl_long,
    cl_ulong,
    cl_half,
    cl_float,
    cl_double>>>;

FCPPT_PP_POP_WARNING

}

#endif
