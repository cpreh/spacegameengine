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


#ifndef SGE_OPENCL_PROGRAM_BUILD_PARAMETERS_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_BUILD_PARAMETERS_HPP_INCLUDED

#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/program/build_options.hpp>
#include <sge/opencl/program/notification_callback.hpp>
#include <sge/opencl/program/optional_notification_callback.hpp>
#include <fcppt/optional/object_impl.hpp>


namespace sge
{
namespace opencl
{
namespace program
{

class build_parameters
{
public:
	SGE_OPENCL_DETAIL_SYMBOL
	build_parameters();

	SGE_OPENCL_DETAIL_SYMBOL
	build_parameters &
	devices(
		sge::opencl::device::object_ref_sequence const &
	);

	SGE_OPENCL_DETAIL_SYMBOL
	build_parameters &
	options(
		sge::opencl::program::build_options const &
	);

	SGE_OPENCL_DETAIL_SYMBOL
	build_parameters &
	notification_callback(
		sge::opencl::program::notification_callback const &
	);

	typedef
	fcppt::optional::object<
		sge::opencl::device::object_ref_sequence
	>
	optional_object_ref_sequence;

	SGE_OPENCL_DETAIL_SYMBOL
	optional_object_ref_sequence const &
	devices() const;

	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::program::build_options const &
	build_options() const;

	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::program::optional_notification_callback const &
	notification_callback() const;
private:
	optional_object_ref_sequence devices_;

	sge::opencl::program::build_options build_options_;

	sge::opencl::program::optional_notification_callback notification_callback_;
};

}
}
}

#endif
