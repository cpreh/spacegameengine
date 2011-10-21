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


#ifndef SGE_OPENCL_MEMORY_OBJECT_RENDERER_BUFFER_LOCK_MODE_TO_CL_MEM_FLAGS_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_RENDERER_BUFFER_LOCK_MODE_TO_CL_MEM_FLAGS_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/memory_object/renderer_buffer_lock_mode.hpp>
#include <fcppt/assert/unreachable.hpp>


namespace sge
{
namespace opencl
{
namespace memory_object
{
inline cl_mem_flags
renderer_buffer_lock_mode_to_cl_mem_flags(
	memory_object::renderer_buffer_lock_mode::type const _lock_mode)
{
	switch(_lock_mode)
	{
		case memory_object::renderer_buffer_lock_mode::read_only:
			return
				CL_MEM_READ_ONLY;
		case renderer_buffer_lock_mode::write_only:
			return
				CL_MEM_WRITE_ONLY;
		case renderer_buffer_lock_mode::read_write:
			return
				CL_MEM_READ_WRITE;
	}
	FCPPT_ASSERT_UNREACHABLE;
}
}
}
}

#endif
