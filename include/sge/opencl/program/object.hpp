/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENCL_PROGRAM_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_OBJECT_HPP_INCLUDED

#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/kernel/object_fwd.hpp>
#include <sge/opencl/program/device_blob_map.hpp>
#include <sge/opencl/program/optional_build_parameters.hpp>
#include <sge/opencl/program/build_parameters_fwd.hpp>
#include <sge/opencl/program/notification_callback.hpp>
#include <sge/opencl/program/source_string_sequence.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opencl
{
namespace program
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_SYMBOL explicit
	object(
		context::object &,
		program::device_blob_map const &,
		program::optional_build_parameters const &);

	SGE_OPENCL_SYMBOL explicit
	object(
		context::object &,
		program::source_string_sequence const &,
		program::optional_build_parameters const &);

	SGE_OPENCL_SYMBOL cl_program
	impl() const;

	SGE_OPENCL_SYMBOL void
	build(
		program::build_parameters const &);

	SGE_OPENCL_SYMBOL program::device_blob_map const
	binaries() const;

	SGE_OPENCL_SYMBOL ~object();
private:
	friend class kernel::object;

	cl_program program_;
	program::notification_callback notification_callback_;

	static void
	notification_callback(
		cl_program,
		void *);
};
}
}
}

#endif
