/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_D3D_INDEX_BUFFER_HPP_INCLUDED
#define SGE_D3D_INDEX_BUFFER_HPP_INCLUDED

#include "../../renderer/index_buffer.hpp"
#include "./resource.hpp"

#include "./d3dinclude.hpp"

namespace sge
{
namespace d3d
{

class renderer;

class index_buffer : public sge::index_buffer, public resource {
	friend class renderer;
public:
	index_buffer(renderer* r, d3d_device_ptr device, size_type size, resource_flag_t flags, const_pointer src);
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;
	size_type size() const;
	void resize(size_type newsize, const_pointer new_data);
	void lock(lock_flag_t flags);
	void unlock();
	void set_data(const_pointer src, size_type first, size_type count);
	resource_flag_t flags() const;
	pointer data();
	const_pointer data() const;
	
	void lock(lock_flag_t lflags, size_type first, size_type count);
private:
	void on_loss();
	void on_reset();

	void init(const_pointer src = 0);

	d3d_device_ptr       device;
	d3d_index_buffer_ptr buffer;
	resource_flag_t      _flags;
	size_type            sz;
	pointer              lock_dest;
};

}
}

#endif
