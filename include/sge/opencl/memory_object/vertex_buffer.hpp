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


#ifndef SGE_OPENCL_MEMORY_OBJECT_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_VERTEX_BUFFER_HPP_INCLUDED

#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/renderer_buffer_lock_mode.hpp>
#include <sge/opencl/context/object_fwd.hpp>
#include <sge/opencl/symbol.hpp>
#include <sge/renderer/vertex_buffer_fwd.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
class SGE_CLASS_SYMBOL vertex_buffer
:
	public memory_object::base
{
FCPPT_NONCOPYABLE(
	vertex_buffer);
public:
	SGE_OPENCL_SYMBOL explicit
	vertex_buffer(
		context::object &,
		sge::renderer::vertex_buffer &,
		memory_object::renderer_buffer_lock_mode::type);

	SGE_OPENCL_SYMBOL cl_mem
	impl();

	SGE_OPENCL_SYMBOL ~vertex_buffer();
private:
	cl_mem impl_;
};
}
}
}

#endif
