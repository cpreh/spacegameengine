//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_KERNEL_NUMERIC_TYPE_HPP_INCLUDED
#define SGE_OPENCL_KERNEL_NUMERIC_TYPE_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <fcppt/config/gcc_version_at_least.hpp>
#include <fcppt/metal/unique.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/from_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opencl
{
namespace kernel
{

FCPPT_PP_PUSH_WARNING
#if FCPPT_CONFIG_GCC_VERSION_AT_LEAST(6,0)
// Alignment does not matter here
FCPPT_PP_DISABLE_GCC_WARNING(-Wignored-attributes)
#endif

typedef
fcppt::variant::from_list<
	fcppt::metal::unique<
		::metal::list<
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
			cl_double
		>
	>
>
numeric_type;

FCPPT_PP_POP_WARNING

}
}
}

#endif
