//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_SINGLE_DEVICE_SYSTEM_PARAMETERS_HPP_INCLUDED
#define SGE_OPENCL_SINGLE_DEVICE_SYSTEM_PARAMETERS_HPP_INCLUDED

#include <sge/opencl/command_queue/execution_mode.hpp>
#include <sge/opencl/command_queue/profiling_mode.hpp>
#include <sge/opencl/context/optional_error_callback.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/single_device_system/optional_renderer.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <fcppt/optional/object_impl.hpp>


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
		sge::renderer::device::core_ref
	);

	SGE_OPENCL_DETAIL_SYMBOL
	parameters &
	enable_profiling();

	SGE_OPENCL_DETAIL_SYMBOL
	parameters &
	context_error_callback(
		sge::opencl::context::error_callback const &
	);

	SGE_OPENCL_DETAIL_SYMBOL
	parameters &
	prefer_gpu(
		bool
	);

	SGE_OPENCL_DETAIL_SYMBOL
	parameters &
	execution_mode(
		sge::opencl::command_queue::execution_mode
	);

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::single_device_system::optional_renderer const &
	renderer() const;

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::context::optional_error_callback const &
	error_callback() const;

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::command_queue::profiling_mode
	profiling() const;

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::command_queue::execution_mode
	execution_mode() const;

	[[nodiscard]]
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
