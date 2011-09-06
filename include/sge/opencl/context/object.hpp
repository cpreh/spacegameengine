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


#ifndef SGE_OPENCL_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/opencl/context/parameters_fwd.hpp>
#include <sge/opencl/context/error_callback.hpp>
#include <sge/opencl/program/object_fwd.hpp>
#include <sge/opencl/command_queue/object_fwd.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/opencl/platform/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <cstddef>
#include <CL/cl.h>

namespace sge
{
namespace opencl
{
namespace context
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_SYMBOL explicit
	object(
		context::parameters const &);

	SGE_OPENCL_SYMBOL cl_context
	impl() const;

	SGE_OPENCL_SYMBOL
	~object();
private:
	friend class opencl::platform::object;
	friend class opencl::command_queue::object;
	friend class opencl::program::object;

	cl_context context_;
	context::error_callback const error_callback_;


	static void
	error_callback(
		char const *,
		void const *,
		size_t,
		void *);
};
}
}
}

#endif
