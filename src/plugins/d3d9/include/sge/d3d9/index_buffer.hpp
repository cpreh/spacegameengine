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


#ifndef SGE_D3D9_INDEX_BUFFER_HPP_INCLUDED
#define SGE_D3D9_INDEX_BUFFER_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/container/bitfield/basic_decl.hpp>


namespace sge
{
namespace d3d9
{

class index_buffer
:
	public sge::renderer::index_buffer,
	public resource
{
	FCPPT_NONCOPYABLE(
		index_buffer
	);
public:
	index_buffer(
		IDirect3DDevice9 *,
		renderer::index::dynamic::format::type,
		count_type,
		renderer::resource_flags_field const &
	);

	~index_buffer();

	view_type const
	lock(
		renderer::lock_mode::type,
		first_type,
		count_type
	);

	const_view_type const
	lock(
		first_type,
		count_type
	) const;

	void
	unlock() const;

	count_type const
	size() const;

	renderer::resource_flags_field const
	resource_flags() const;

	renderer::index::dynamic::format::type
	format() const;

	IDirect3DIndexBuffer9 *
	get() const;
private:
	void
	init();

	void
	on_loss();

	void
	on_reset();

	template<
		typename View
	>
	View const
	do_lock(
		first_type,
		count_type,
		renderer::lock_flags::method::type
	) const;

	IDirect3DDevice9 *const device_;

	typedef fcppt::scoped_ptr<
		IDirect3DIndexBuffer9,
		fcppt::com_deleter
	> d3d_scoped_index_buffer_ptr;

	d3d_scoped_index_buffer_ptr buffer_;

	renderer::resource_flags_field const resource_flags_;

	renderer::index::dynamic::format::type const format_;

	count_type const size_;
	
	size_type const stride_;

	mutable renderer::raw_pointer lock_dest_;
};

}
}

#endif
