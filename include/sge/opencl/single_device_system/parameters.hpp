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


#ifndef SGE_OPENCL_SINGLE_DEVICE_SYSTEM_PARAMETERS_HPP_INCLUDED
#define SGE_OPENCL_SINGLE_DEVICE_SYSTEM_PARAMETERS_HPP_INCLUDED

#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/command_queue/execution_mode.hpp>
#include <sge/opencl/command_queue/profiling_mode.hpp>
#include <sge/opencl/context/optional_error_callback.hpp>
#include <sge/opencl/single_device_system/optional_renderer.hpp>
#include <fcppt/optional_impl.hpp>


namespace sge
{
namespace opencl
{
namespace single_device_system
{
class parameters
{
public:
	SGE_OPENCL_DETAIL_SYMBOL
	parameters();

	SGE_OPENCL_DETAIL_SYMBOL
	parameters &
	renderer(
		sge::renderer::device::core &);

	SGE_OPENCL_DETAIL_SYMBOL
	parameters &
	enable_profiling();

	SGE_OPENCL_DETAIL_SYMBOL
	parameters &
	context_error_callback(
		sge::opencl::context::error_callback const &);

	SGE_OPENCL_DETAIL_SYMBOL
	parameters &
	prefer_gpu(
		bool);

	SGE_OPENCL_DETAIL_SYMBOL
	parameters &
	execution_mode(
		sge::opencl::command_queue::execution_mode);

	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::single_device_system::optional_renderer const &
	renderer() const;

	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::context::optional_error_callback const &
	error_callback() const;

	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::command_queue::profiling_mode
	profiling() const;

	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::command_queue::execution_mode
	execution_mode() const;

	SGE_OPENCL_DETAIL_SYMBOL
	bool
	prefers_gpu() const;
private:
	sge::opencl::single_device_system::optional_renderer renderer_;
	sge::opencl::context::optional_error_callback error_callback_;
	sge::opencl::command_queue::profiling_mode profiling_;
	sge::opencl::command_queue::execution_mode execution_mode_;
	bool prefers_gpu_;
};
}
}
}

#endif
