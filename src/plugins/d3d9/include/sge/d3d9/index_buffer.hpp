/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/renderer/lock_mode_fwd.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_parameters_fwd.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/lock_flags/method_fwd.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/unique_ptr_decl.hpp>


namespace sge
{
namespace d3d9
{

class index_buffer
:
	public sge::renderer::index::buffer,
	public sge::d3d9::resource
{
	FCPPT_NONCOPYABLE(
		index_buffer
	);
public:
	index_buffer(
		IDirect3DDevice9 &,
		sge::renderer::index::buffer_parameters const &
	);

	~index_buffer();

	view_type const
	lock(
		sge::renderer::lock_mode,
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

	sge::renderer::resource_flags_field const
	resource_flags() const;

	sge::renderer::index::dynamic::format
	format() const;

	IDirect3DIndexBuffer9 &
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
		sge::renderer::lock_flags::method
	) const;

	IDirect3DDevice9 &device_;

	typedef
	fcppt::unique_ptr<
		IDirect3DIndexBuffer9,
		fcppt::com_deleter
	>
	d3d_index_buffer_unique_ptr;

	typedef
	fcppt::optional<
		d3d_index_buffer_unique_ptr
	>
	optional_d3d_index_buffer_unique_ptr;

	optional_d3d_index_buffer_unique_ptr buffer_;

	sge::renderer::resource_flags_field const resource_flags_;

	sge::renderer::index::dynamic::format const format_;

	count_type const size_;

	size_type const stride_;

	mutable sge::renderer::raw_pointer lock_dest_;
};

}
}

#endif
