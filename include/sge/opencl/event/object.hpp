/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENCL_EVENT_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_EVENT_OBJECT_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opencl
{
namespace event
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_OPENCL_SYMBOL
	object();

	SGE_OPENCL_SYMBOL
	cl_event &
	handle();

	SGE_OPENCL_SYMBOL
	cl_event const &
	handle() const;

	SGE_OPENCL_SYMBOL
	~object();
private:
	cl_event handle_;
	mutable bool handle_retrieved_;
};
}
}
}

#endif

