//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	build_parameters
	devices(
		sge::opencl::device::object_ref_sequence &&
	) &&;

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	build_parameters
	options(
		sge::opencl::program::build_options &&
	) &&;

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	build_parameters
	notification_callback(
		sge::opencl::program::notification_callback &&
	) &&;

	using
	optional_object_ref_sequence
	=
	fcppt::optional::object<
		sge::opencl::device::object_ref_sequence
	>;

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	optional_object_ref_sequence const &
	devices() const;

	[[nodiscard]]
	SGE_OPENCL_DETAIL_SYMBOL
	sge::opencl::program::build_options const &
	build_options() const;

	[[nodiscard]]
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
