#ifndef SGE_OPENCL_SINGLE_DEVICE_SYSTEM_PARAMETERS_HPP_INCLUDED
#define SGE_OPENCL_SINGLE_DEVICE_SYSTEM_PARAMETERS_HPP_INCLUDED

#include <sge/opencl/symbol.hpp>
#include <sge/opencl/optional_renderer.hpp>
#include <sge/opencl/context/optional_error_callback.hpp>
#include <sge/opencl/command_queue/profiling_mode.hpp>

namespace sge
{
namespace opencl
{
namespace single_device_system
{
class parameters
{
public:
	SGE_OPENCL_SYMBOL
	explicit
	parameters();

	SGE_OPENCL_SYMBOL
	parameters &
	renderer(
		sge::renderer::device &);

	SGE_OPENCL_SYMBOL
	parameters &
	enable_profiling();

	SGE_OPENCL_SYMBOL
	parameters &
	context_error_callback(
		opencl::context::error_callback const &);

	SGE_OPENCL_SYMBOL
	parameters &
	prefer_gpu();

	SGE_OPENCL_SYMBOL
	opencl::optional_renderer const &
	renderer() const;

	SGE_OPENCL_SYMBOL
	opencl::context::optional_error_callback const &
	error_callback() const;

	SGE_OPENCL_SYMBOL
	command_queue::profiling_mode::type
	profiling() const;

	SGE_OPENCL_SYMBOL
	bool
	prefers_gpu() const;
private:
	opencl::optional_renderer renderer_;
	opencl::context::optional_error_callback error_callback_;
	command_queue::profiling_mode::type profiling_;
	bool prefers_gpu_;
};
}
}
}

#endif
