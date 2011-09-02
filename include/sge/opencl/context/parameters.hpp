#ifndef SGE_OPENCL_CONTEXT_PARAMETERS_HPP_INCLUDED
#define SGE_OPENCL_CONTEXT_PARAMETERS_HPP_INCLUDED

#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/context/error_callback.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace opencl
{
namespace context
{
class parameters
{
FCPPT_NONASSIGNABLE(
	parameters);
public:
	SGE_OPENCL_SYMBOL explicit
	parameters(
		platform::object &,
		opencl::device::object_ref_sequence const &);

	SGE_OPENCL_SYMBOL opencl::context::parameters &
	error_callback(
		context::error_callback const &);

	SGE_OPENCL_SYMBOL context::parameters &
	share_with(
		renderer::device &);

	SGE_OPENCL_SYMBOL opencl::device::object_ref_sequence const &
	device_refs() const;

	SGE_OPENCL_SYMBOL context::error_callback const &
	error_callback() const;

	SGE_OPENCL_SYMBOL renderer::device *
	shared_renderer() const;

	SGE_OPENCL_SYMBOL platform::object &
	platform() const;
private:
	platform::object &platform_;
	device::object_ref_sequence device_refs_;
	context::error_callback error_callback_;
	renderer::device *shared_renderer_;
};
}
}
}

#endif
