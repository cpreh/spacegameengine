/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opencl/optional_renderer.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/system_fwd.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/command_queue/profiling_mode.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/context/optional_error_callback.hpp>
#include <sge/opencl/device/object_fwd.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <sge/opencl/single_device_system/parameters_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/thread/mutex.hpp>
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
		single_device_system::parameters const &);

	SGE_OPENCL_SYMBOL opencl::system &
	system();

	SGE_OPENCL_SYMBOL opencl::system const &
	system() const;

	SGE_OPENCL_SYMBOL void
	update();

	SGE_OPENCL_SYMBOL platform::object &
	platform();

	SGE_OPENCL_SYMBOL platform::object const &
	platform() const;

	SGE_OPENCL_SYMBOL device::object &
	device();

	SGE_OPENCL_SYMBOL device::object const &
	device() const;

	SGE_OPENCL_SYMBOL context::object &
	context();

	SGE_OPENCL_SYMBOL context::object const &
	context() const;

	SGE_OPENCL_SYMBOL command_queue::object &
	command_queue();

	SGE_OPENCL_SYMBOL command_queue::object const &
	command_queue() const;

	SGE_OPENCL_SYMBOL
	~object();
private:
	fcppt::scoped_ptr<opencl::system> system_;
	platform::object *platform_;
	device::object *device_;
	fcppt::scoped_ptr<context::object> context_;
	fcppt::scoped_ptr<command_queue::object> queue_;
	boost::mutex error_mutex_;
	bool error_occured_;
	opencl::error_information_string error_information_;
	opencl::binary_error_data error_data_;
	context::optional_error_callback const error_callback_;

	void
	error_callback(
		opencl::error_information_string const &,
		opencl::binary_error_data const &);
};
}
}
}

#endif
