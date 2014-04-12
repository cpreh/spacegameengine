/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENCL_SINGLE_DEVICE_SYSTEM_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_SINGLE_DEVICE_SYSTEM_OBJECT_HPP_INCLUDED

#include <sge/opencl/binary_error_data.hpp>
#include <sge/opencl/error_information_string.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/system_fwd.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/command_queue/profiling_mode.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/context/optional_error_callback.hpp>
#include <sge/opencl/device/object_fwd.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <sge/opencl/single_device_system/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <mutex>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opencl
{
namespace single_device_system
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_SYMBOL explicit
	object(
		sge::opencl::single_device_system::parameters const &);

	SGE_OPENCL_SYMBOL sge::opencl::system &
	system();

	SGE_OPENCL_SYMBOL sge::opencl::system const &
	system() const;

	SGE_OPENCL_SYMBOL void
	update();

	SGE_OPENCL_SYMBOL sge::opencl::platform::object &
	platform();

	SGE_OPENCL_SYMBOL sge::opencl::platform::object const &
	platform() const;

	SGE_OPENCL_SYMBOL sge::opencl::device::object &
	device();

	SGE_OPENCL_SYMBOL sge::opencl::device::object const &
	device() const;

	SGE_OPENCL_SYMBOL sge::opencl::context::object &
	context();

	SGE_OPENCL_SYMBOL sge::opencl::context::object const &
	context() const;

	SGE_OPENCL_SYMBOL sge::opencl::command_queue::object &
	command_queue();

	SGE_OPENCL_SYMBOL sge::opencl::command_queue::object const &
	command_queue() const;

	SGE_OPENCL_SYMBOL
	~object();
private:
	std::unique_ptr<sge::opencl::system> const system_;
	sge::opencl::platform::object *platform_;
	sge::opencl::device::object *device_;
	std::unique_ptr<sge::opencl::context::object> const context_;
	std::unique_ptr<sge::opencl::command_queue::object> const queue_;
	std::mutex error_mutex_;
	bool error_occured_;
	sge::opencl::error_information_string error_information_;
	sge::opencl::binary_error_data error_data_;
	sge::opencl::context::optional_error_callback const error_callback_;

	void
	error_callback(
		sge::opencl::error_information_string const &,
		sge::opencl::binary_error_data const &);
};
}
}
}

#endif
