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


#ifndef SGE_OPENCL_PROGRAM_BUILD_PARAMETERS_HPP_INCLUDED
#define SGE_OPENCL_PROGRAM_BUILD_PARAMETERS_HPP_INCLUDED

#include <sge/opencl/symbol.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/program/build_options.hpp>
#include <sge/opencl/program/notification_callback.hpp>
#include <fcppt/optional.hpp>


namespace sge
{
namespace opencl
{
namespace program
{
class build_parameters
{
public:
	SGE_OPENCL_SYMBOL explicit
	build_parameters();

	SGE_OPENCL_SYMBOL program::build_parameters &
	devices(
		device::object_ref_sequence const &);

	SGE_OPENCL_SYMBOL program::build_parameters &
	options(
		program::build_options const &);

	SGE_OPENCL_SYMBOL program::build_parameters &
	notification_callback(
		program::notification_callback const &);

	SGE_OPENCL_SYMBOL fcppt::optional<device::object_ref_sequence> const &
	devices() const;

	SGE_OPENCL_SYMBOL program::build_options const &
	build_options() const;

	SGE_OPENCL_SYMBOL program::notification_callback const &
	notification_callback() const;
private:
	fcppt::optional<device::object_ref_sequence> devices_;
	program::build_options build_options_;
	program::notification_callback notification_callback_;
};
}
}
}

#endif
