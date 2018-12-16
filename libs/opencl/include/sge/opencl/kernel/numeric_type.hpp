/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_OPENCL_KERNEL_NUMERIC_TYPE_HPP_INCLUDED
#define SGE_OPENCL_KERNEL_NUMERIC_TYPE_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <fcppt/brigand/unique.hpp>
#include <fcppt/config/gcc_version_at_least.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
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
fcppt::variant::object<
	fcppt::brigand::unique<
		::brigand::list<
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
