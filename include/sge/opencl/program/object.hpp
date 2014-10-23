/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/kernel/object_fwd.hpp>
#include <sge/opencl/program/build_parameters_fwd.hpp>
#include <sge/opencl/program/device_blob_map.hpp>
#include <sge/opencl/program/notification_callback.hpp>
#include <sge/opencl/program/optional_build_parameters.hpp>
#include <sge/opencl/program/source_string_sequence.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/container/raw_vector.hpp>


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
	SGE_OPENCL_DETAIL_SYMBOL
	object(
		sge::opencl::context::object &,
		sge::opencl::program::device_blob_map const &,
		sge::opencl::program::optional_build_parameters const &);

	SGE_OPENCL_DETAIL_SYMBOL
	object(
		sge::opencl::context::object &,
		sge::opencl::program::source_string_sequence const &,
		sge::opencl::program::optional_build_parameters const &);

	SGE_OPENCL_DETAIL_SYMBOL cl_program
	impl() const;

	SGE_OPENCL_DETAIL_SYMBOL void
	build(
		sge::opencl::program::build_parameters const &);

	SGE_OPENCL_DETAIL_SYMBOL sge::opencl::program::device_blob_map const
	binaries() const;

	SGE_OPENCL_DETAIL_SYMBOL ~object();
private:
	friend class sge::opencl::kernel::object;

	typedef
	fcppt::container::raw_vector<cl_device_id>
	device_id_vector;

	cl_program program_;
	sge::opencl::program::notification_callback notification_callback_;

	device_id_vector const
	program_devices() const;

	void
	check_program_return_values();

	static void
	notification_callback(
		cl_program,
		void *);
};
}
}
}

#endif
