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


#include <sge/renderer/device.hpp>
#include <sge/renderer/index/copy.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/index_buffer.hpp>
#include <sge/renderer/vertex_buffer.hpp>
#include <sge/renderer/indices_per_primitive.hpp>
#include <sge/renderer/vf/dynamic_format.hpp>
#include <sge/renderer/index/view_format.hpp>
#include <sge/renderer/index/view_size.hpp>
#include <sge/image/view/format.hpp>
#include <sge/image/view/dim.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/algorithm/copy_n.hpp>
#include <boost/variant/apply_visitor.hpp>

sge::renderer::texture_ptr const sge::renderer::device::no_texture;
sge::renderer::texture_ptr const sge::renderer::device::default_target;
sge::renderer::glsl::program_ptr const sge::renderer::device::no_program;

sge::renderer::device::device()
{}

void
sge::renderer::device::render(
	const_vertex_buffer_ptr const vb,
	nonindexed_primitive_type::type const ptype)
{
	render(
		vb,
		0,
		vb->size(),
		ptype
	);
}

void
sge::renderer::device::render(
	const_vertex_buffer_ptr const vb,
	const_index_buffer_ptr const ib,
	indexed_primitive_type::type const ptype)
{
	size_type const ipp(
		indices_per_primitive(
			ptype
		)
	);

	SGE_ASSERT(
		ib->size() % ipp == 0
	);

	render(
		vb,
		ib,
		0,
		vb->size(),
		ptype,
		ib->size() / ipp,
		0
	);
}

sge::renderer::texture_ptr const
sge::renderer::device::create_texture(
	image::view::const_object const &v,
	filter::texture const &filter,
	resource_flag_t const flags)
{
	texture_ptr const tex(
		create_texture(
			image::view::dim(v),
			image::view::format(v),
			filter,
			flags
		)
	);
	
	scoped_texture_lock const lock(
		tex,
		lock_flags::writeonly
	);

	image::algorithm::copy_and_convert(
		v,
		lock.value()
	);

	return tex;
}

/*
sge::renderer::volume_texture_ptr const
sge::renderer::device::create_volume_texture(
	image::view::const_object3 const &,
	filter::texture const &filter,
	resource_flag_t const flags
)
{
	volume_texture_ptr const tex(
		create_volume_texture(
			image::view::dim(v),
			image::view::format::(v),
			filter,
			flags
		)
	);

	scopde_volume_texture_lock const lock(
		tex,
		lock_flags::writeonly
	);

	image::algorithm::copy_and_convert(
		v,
		lock.value()
	);

	return tex;
}
*/


sge::renderer::vertex_buffer_ptr const
sge::renderer::device::create_vertex_buffer(
	vf::const_dynamic_view const &view,
	resource_flag_t const flags)
{
	vertex_buffer_ptr const vb(
		create_vertex_buffer(
			view.format(),
			view.size(),
			flags
		)
	);
	
	scoped_vertex_lock const lock(
		vb,
		lock_flags::writeonly
	);
	
	algorithm::copy_n(
		view.data(),
		view.format().stride() * view.size(),
		lock.value().data()
	);

	return vb;
}

sge::renderer::index_buffer_ptr const
sge::renderer::device::create_index_buffer(
	index::const_view const &view,
	resource_flag_t const flags)
{
	index_buffer_ptr const ib(
		create_index_buffer(
			index::view_format(
				view),
			index::view_size(
				view),
			flags
		)
	);
	
	scoped_index_lock const lock(
		ib,
		lock_flags::writeonly
	);
	
	index::copy(
		view,
		lock.value()
	);
	
	return ib;
}

sge::renderer::device::~device()
{}
