/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENCL_PLATFORM_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_PLATFORM_OBJECT_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/extension_sequence.hpp>
#include <sge/opencl/profile_type.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/system_fwd.hpp>
#include <sge/opencl/version.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/context/parameters_fwd.hpp>
#include <sge/opencl/device/object.hpp>
#include <sge/opencl/device/object_sequence.hpp>
#include <sge/renderer/device_fwd.hpp>
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
