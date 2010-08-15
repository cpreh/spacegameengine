/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_D3D9_VERTEX_BUFFER_HPP_INCLUDED

#include "vertex_format.hpp"
#include "resource.hpp"
#include "d3dinclude.hpp"
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/raw_pointer.hpp>

namespace sge
{
namespace d3d9
{

class vertex_buffer
:
	public sge::renderer::vertex_buffer,
	public resource
{
public:
	vertex_buffer(
		d3d_device_ptr device,
		renderer::vf::dynamic_format const &,
		size_type size,
		resource_flag_type flags);

	view_type const
	lock(
		lock_flag_type flags,
		size_type offset,
		size_type range);

	const_view_type const
	lock(
		size_type offset,
		size_type range) const;

	void unlock() const;

	size_type size() const;

	resource_flag_type flags() const;

	renderer::vf::dynamic_format const &
	format() const;
private:
	void init();
	void on_loss();
	void on_reset();

	void
	do_lock(
		DWORD flags,
		size_type offset,
		size_type range
	) const;

	size_type stride() const;

	d3d_device_ptr const  device_;
	d3d_vertex_buffer_ptr buffer;
	mutable renderer::raw_pointer lock_dest;
	resource_flag_type const flags_;
	size_type const       sz;
	vertex_format const   d3d_format;
};

}
}

#endif
