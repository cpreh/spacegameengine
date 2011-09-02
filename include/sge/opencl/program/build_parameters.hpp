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
