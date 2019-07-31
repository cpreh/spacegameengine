//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_PLATFORM_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_PLATFORM_OBJECT_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/system_fwd.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/context/parameters_fwd.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/device/object_sequence.hpp>
#include <sge/opencl/platform/extension_sequence.hpp>
#include <sge/opencl/platform/profile_type_fwd.hpp>
#include <sge/opencl/platform/version.hpp>
#include <sge/renderer/device/core_fwd.hpp>
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
	SGE_OPENCL_DETAIL_SYMBOL cl_platform_id
	impl() const;

	SGE_OPENCL_DETAIL_SYMBOL opencl::device::object_sequence &
	devices();

	SGE_OPENCL_DETAIL_SYMBOL opencl::device::object_sequence const &
	devices() const;

	SGE_OPENCL_DETAIL_SYMBOL sge::opencl::platform::profile_type
	profile() const;

	SGE_OPENCL_DETAIL_SYMBOL sge::opencl::platform::version
	version() const;

	SGE_OPENCL_DETAIL_SYMBOL std::string
	name() const;

	SGE_OPENCL_DETAIL_SYMBOL std::string
	vendor() const;

	SGE_OPENCL_DETAIL_SYMBOL sge::opencl::platform::extension_sequence
	extensions() const;

	SGE_OPENCL_DETAIL_SYMBOL bool
	supports_memory_sharing_with(
		renderer::device::core const &) const;

	SGE_OPENCL_DETAIL_SYMBOL bool
	has_gpu() const;

	SGE_OPENCL_DETAIL_SYMBOL
	~object();

	object(
		object &&
	);

	object &
	operator=(
		object &&
	);
private:
	friend class opencl::system;
	friend class opencl::context::object;

	cl_platform_id platform_id_;

	opencl::device::object_sequence devices_;

	explicit
	object(
		cl_platform_id const &);
};
}
}
}

#endif
