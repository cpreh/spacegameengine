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
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/index/view_format.hpp>
#include <sge/renderer/index/view_size.hpp>
#include <sge/image/view/format.hpp>
#include <sge/image/view/dim.hpp>
#include <sge/image/algorithm/copy_and_convert.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/assert.hpp>
#include <boost/variant/apply_visitor.hpp>

sge::renderer::texture_ptr const sge::renderer::device::no_texture;
sge::renderer::texture_ptr const sge::renderer::device::default_target;
sge::renderer::glsl::program_ptr const sge::renderer::device::no_program;

sge::renderer::device::device()
{}

void
sge::renderer::device::render(
	const_vertex_buffer_ptr const vb,
	nonindexed_primitive_type::type const ptype
)
{
	set_vertex_buffer(
		vb
	);

	render(
		first_vertex(0),
		vertex_count(
			vb->size()
		),
		ptype
	);
}

void
sge::renderer::device::render(
	const_vertex_buffer_ptr const vb,
	const_index_buffer_ptr const ib,
	indexed_primitive_type::type const ptype
)
{
	set_vertex_buffer(
		vb
	);

	size_type const ipp(
		indices_per_primitive(
			ptype
		)
	);

	FCPPT_ASSERT(
		ib->size() % ipp == 0
	);

	render(
		ib,
		first_vertex(0),
		vertex_count(
			vb->size()
		),
		ptype,
		primitive_count(ib->size() / ipp),
		first_index(0)
	);
}

sge::renderer::texture_ptr const
sge::renderer::device::create_texture(
	image::view::const_object const &v,
	filter::texture const &filter,
	resource_flags_field const &flags
)
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
		lock_mode::writeonly
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
	resource_flags_field const & const flags
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
		lock_mode::writeonly
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
	vf::dynamic::const_view const &view,
	resource_flags_field const &flags
)
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
		lock_mode::writeonly
	);

	fcppt::algorithm::copy_n(
		view.data(),
		view.format().stride() * view.size(),
		lock.value().data()
	);

	return vb;
}

sge::renderer::index_buffer_ptr const
sge::renderer::device::create_index_buffer(
	index::const_view const &view,
	resource_flags_field const &flags
)
{
	index_buffer_ptr const ib(
		create_index_buffer(
			index::view_format(
				view
			),
			index::view_size(
				view
			),
			flags
		)
	);

	scoped_index_lock const lock(
		ib,
		lock_mode::writeonly
	);

	index::copy(
		view,
		lock.value()
	);

	return ib;
}

sge::renderer::device::~device()
{}
