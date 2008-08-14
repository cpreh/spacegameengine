/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/image_view_algorithm.hpp>
#include <sge/renderer/image_view_format.hpp>
#include <sge/renderer/image_view_dim.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/index_view_operations.hpp>
#include <sge/renderer/scoped_index_lock.hpp>
#include <sge/renderer/vertex_format.hpp>
#include <sge/renderer/scoped_vertex_lock.hpp>
#include <sge/algorithm.hpp>
#include <boost/variant/apply_visitor.hpp>

const sge::renderer::texture_ptr sge::renderer::device::no_texture;
const sge::renderer::texture_ptr sge::renderer::device::default_render_target;
const sge::renderer::glsl::program_ptr sge::renderer::device::no_program;


sge::renderer::texture_ptr const
sge::renderer::device::create_texture(
	const_image_view const &v,
	filter_args const &filter,
	resource_flag_t const flags)
{
	texture_ptr const tex(
		create_texture(
			texture::dim_type(image_view_dim(v)),
			image_view_format(v),
			filter,
			flags));
	
	scoped_texture_lock const lock(
		make_scoped_lock(
			tex,
			lock_flags::writeonly));

	copy_and_convert_pixels(
		v,
		lock.value());
}

sge::renderer::vertex_buffer_ptr const
sge::renderer::device::create_vertex_buffer(
	const_vertex_view const &view,
	resource_flag_t const flags)
{
	vertex_buffer_ptr const vb(
		create_vertex_buffer(
			view.format(),
			view.size(),
			flags));
	
	scoped_vertex_lock const lock(
		make_scoped_lock(
			vb,
			lock_flags::writeonly));
	
	copy_n(
		view.data(),
		view.format().stride() * view.size(),
		lock.value().data());
}

sge::renderer::index_buffer_ptr const
sge::renderer::device::create_index_buffer(
	const_dynamic_index_view const &view,
	resource_flag_t const flags)
{
	index_buffer::size_type const sz(
		boost::apply_visitor(
			index_view_size(),
			view));

	index_buffer_ptr const ib(
		create_index_buffer(
			boost::apply_visitor(
				index_view_format(),
				view),
			sz,
			flags));
	
	scoped_index_lock const lock(
		make_scoped_lock(
			ib,
			lock_flags::writeonly));
	
	copy_n(
		boost::apply_visitor(
			index_view_data_const(),
			view),
		sz * boost::apply_visitor(
			index_view_stride(),
			view),
		boost::apply_visitor(
			index_view_data(),
			lock.value()));
}

sge::renderer::screen_unit
sge::renderer::device::screen_width() const
{
	return screen_size().w();
}

sge::renderer::screen_unit
sge::renderer::device::screen_height() const
{
	return screen_size().h();
}

sge::space_unit
sge::renderer::device::aspect() const
{
	return static_cast<space_unit>(screen_width())
	     / static_cast<space_unit>(screen_height());
}

sge::renderer::device::~device()
{}
