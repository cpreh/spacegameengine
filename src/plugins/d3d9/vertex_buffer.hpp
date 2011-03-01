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


#ifndef SGE_D3D9_VERTEX_BUFFER_HPP_INCLUDED
#define SGE_D3D9_VERTEX_BUFFER_HPP_INCLUDED

#include "d3dinclude.hpp"
#include "lock_flags.hpp"
#include "resource.hpp"
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <fcppt/container/bitfield/basic_decl.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace d3d9
{

class vertex_buffer
:
	public sge::renderer::vertex_buffer,
	public d3d9::resource
{
	FCPPT_NONCOPYABLE(
		vertex_buffer
	);
public:
	vertex_buffer(
		IDirect3DDevice9 *,
		renderer::vf::dynamic::part const &,
		renderer::vf::dynamic::part_index,
		size_type size,
		renderer::resource_flags_field const &
	);

	~vertex_buffer();

	view_type const
	lock(
		renderer::lock_mode::type,
		size_type offset,
		size_type range
	);

	const_view_type const
	lock(
		size_type offset,
		size_type range
	) const;

	void
	unlock() const;

	size_type
	size() const;

	renderer::resource_flags_field const
	resource_flags() const;

	renderer::vf::dynamic::part const
	format_part() const;

	renderer::vf::dynamic::part_index const
	format_part_index() const;
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
		size_type offset,
		size_type range,
		d3d9::lock_flags
	) const;

	size_type
	stride() const;

	IDirect3DDevice9 *const device_;

	renderer::vf::dynamic::part const format_part_;

	renderer::vf::dynamic::part_index const format_part_index_;

	size_type const size_;

	renderer::resource_flags_field const resource_flags_;

	typedef fcppt::scoped_ptr<
		IDirect3DVertexBuffer9,
		fcppt::com_deleter
	> d3d_scoped_vertex_buffer_ptr;
	
	d3d_scoped_vertex_buffer_ptr buffer_;

	mutable renderer::raw_pointer lock_dest_;
};

}
}

#endif
