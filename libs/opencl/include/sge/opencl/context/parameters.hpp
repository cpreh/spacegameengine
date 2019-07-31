//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_CONTEXT_PARAMETERS_HPP_INCLUDED
#define SGE_OPENCL_CONTEXT_PARAMETERS_HPP_INCLUDED

#include <sge/opencl/context/error_callback.hpp>
#include <sge/opencl/context/optional_error_callback.hpp>
#include <sge/opencl/context/parameters_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/device/object_ref_sequence.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace opencl
{
namespace context
{

class parameters
{
public:
	typedef
	fcppt::optional::reference<
		sge::renderer::device::core
	>
	optional_renderer;

	SGE_OPENCL_DETAIL_SYMBOL
	parameters(
		sge::opencl::platform::object &,
		sge::opencl::device::object_ref_sequence const &
	);

	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::context::parameters &
	error_callback(
		sge::opencl::context::error_callback const &
	);

	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::context::parameters &
	share_with(
		sge::renderer::device::core &
	);

	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::device::object_ref_sequence const &
	device_refs() const;

	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::context::optional_error_callback const &
	error_callback() const;

	SGE_OPENCL_DETAIL_SYMBOL
	optional_renderer const &
	shared_renderer() const;

	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::platform::object &
	platform() const;
private:
	fcppt::reference<
		sge::opencl::platform::object
	> platform_;

	sge::opencl::device::object_ref_sequence device_refs_;

	sge::opencl::context::optional_error_callback error_callback_;

	optional_renderer shared_renderer_;
};

}
}
}

#endif
