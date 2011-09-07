#ifndef SGE_OPENCL_SINGLE_DEVICE_SYSTEM_HPP_INCLUDED
#define SGE_OPENCL_SINGLE_DEVICE_SYSTEM_HPP_INCLUDED

#include <sge/opencl/system_fwd.hpp>
#include <sge/opencl/error_information_string.hpp>
#include <sge/opencl/binary_error_data.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <sge/opencl/device/object_fwd.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace opencl
{
class single_device_system
{
FCPPT_NONCOPYABLE(
	single_device_system);
public:
	SGE_OPENCL_SYMBOL explicit
	single_device_system(
		renderer::device &);

	SGE_OPENCL_SYMBOL opencl::system &
	system();

	SGE_OPENCL_SYMBOL opencl::system const &
	system() const;

	SGE_OPENCL_SYMBOL platform::object &
	platform();

	SGE_OPENCL_SYMBOL platform::object const &
	platform() const;

	SGE_OPENCL_SYMBOL device::object &
	device();

	SGE_OPENCL_SYMBOL device::object const &
	device() const;

	SGE_OPENCL_SYMBOL command_queue::object &
	queue();

	SGE_OPENCL_SYMBOL command_queue::object const &
	queue() const;

	SGE_OPENCL_SYMBOL
	~single_device_system();
private:
	fcppt::scoped_ptr<opencl::system> system_;
	platform::object *platform_;
	device::object *device_;
	fcppt::scoped_ptr<context::object> context_;
	fcppt::scoped_ptr<command_queue::object> queue_;

	void
	error_callback(
		opencl::error_information_string const &,
		opencl::binary_error_data const &);
};
}
}

#endif
