/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#ifndef SGE_D3D9_INDEX_BUFFER_HPP_INCLUDED
#define SGE_D3D9_INDEX_BUFFER_HPP_INCLUDED

#include "resource.hpp"
#include "d3dinclude.hpp"
#include <sge/renderer/index_buffer.hpp>

namespace sge
{
namespace d3d9
{

class index_buffer
:
	public sge::renderer::index_buffer,
	public resource
{
public:
	index_buffer(
		d3d_device_ptr,
		size_type size,
		renderer::index::format,
		resource_flag_type flags);

	size_type size() const;

	view_type const
	lock(
		lock_flag_t flags,
		size_type first,
		size_type count);

	const_view_type const
	lock(
		size_type first,
		size_type count) const;

	void unlock() cibst;

	resource_flag_type flags() const;
private:
	void init();

	void on_loss();
	void on_reset();

	view_type const
	lock(
		DWORD flags,
		size_type first,
		size_type count) const;

	d3d_device_ptr const device_;
	d3d_index_buffer_ptr buffer;
	resource_flag_type const flags_;
	size_type const sz;
	mutable pointer lock_dest;
};

}
}

#endif
