#ifndef SGE_OPENCL_PLATFORM_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_PLATFORM_OBJECT_HPP_INCLUDED

#include <sge/opencl/device/object_sequence.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/context/parameters_fwd.hpp>
#include <sge/opencl/extension_sequence.hpp>
#include <sge/opencl/profile_type.hpp>
#include <sge/opencl/system_fwd.hpp>
#include <sge/opencl/version.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <CL/cl.h>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opencl
{
namespace platform
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_SYMBOL cl_platform_id
	impl() const;

	SGE_OPENCL_SYMBOL opencl::device::object_sequence &
	devices();

	SGE_OPENCL_SYMBOL opencl::device::object_sequence const &
	devices() const;

	SGE_OPENCL_SYMBOL opencl::profile_type::type
	profile() const;

	SGE_OPENCL_SYMBOL opencl::version const
	version() const;

	SGE_OPENCL_SYMBOL std::string const
	name() const;

	SGE_OPENCL_SYMBOL std::string const
	vendor() const;

	SGE_OPENCL_SYMBOL opencl::extension_sequence const
	extensions() const;

	SGE_OPENCL_SYMBOL bool
	supports_memory_sharing_with(
		renderer::device const &) const;

	SGE_OPENCL_SYMBOL
	~object();
private:
	friend class opencl::system;
	friend class opencl::context::object;

	cl_platform_id const platform_id_;
	opencl::device::object_sequence devices_;

	explicit
	object(
		cl_platform_id const &);
};
}
}
}

#endif
