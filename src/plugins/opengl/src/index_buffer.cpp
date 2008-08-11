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


#include "../basic_buffer_impl.hpp"
#include "../index_buffer.hpp"
#include <sge/renderer/index_view_operations.hpp>
#include <boost/variant/apply_visitor.hpp>

SGE_OPENGL_INSTANTIATE_BUFFER_BASE(
	sge::renderer::index_buffer,
	sge::ogl::index_buffer_type,
	sge::ogl::vb_ib_vbo_impl)


sge::ogl::index_buffer::index_buffer(
	renderer::const_dynamic_index_view const &src,
	renderer::resource_flag_t const flags)
: detail::index_buffer_base(
	boost::apply_visitor(renderer::index_view_size(), src),
	boost::apply_visitor(renderer::index_view_stride(), src),
	flags,
	boost::apply_visitor(renderer::index_view_data(), src))
{}

/*void sge::ogl::index_buffer::data(
	renderer::const_dynamic_index_view const &src)
{
	detail::index_buffer_base::data(
		boost::apply_visitor(renderer::index_view_data(), src),
		boost::apply_visitor(renderer::index_view_size(), src),
		boost::apply_visitor(renderer::index_view_stride(), src));
}
	
void sge::ogl::index_buffer::do_sub_data(
	renderer::const_dynamic_index_view const &src,
	size_type const offset)
{
	detail::index_buffer_base::sub_data(
		boost::apply_visitor(renderer::index_view_data(), src),
		offset,
		boost::apply_visitor(renderer::index_view_size(), src));
}*/

// TODO: how can we simplify this?
sge::renderer::dynamic_index_view const
sge::ogl::index_buffer::view()
{
	switch(detail::index_buffer_base::stride()) {
	case sizeof(uint16):
		return renderer::index_view_16(
			reinterpret_cast<renderer::index_view_16::pointer>(
				detail::index_buffer_base::data()),
			lock_size());
	case sizeof(uint32):
		return renderer::index_view_32(
			reinterpret_cast<renderer::index_view_32::pointer>(
				detail::index_buffer_base::data()),
			lock_size());
	default:
		throw exception(SGE_TEXT("Invalid stride in ogl::index_buffer::view()!"));
	}
}

sge::renderer::const_dynamic_index_view const
sge::ogl::index_buffer::view() const
{
	switch(detail::index_buffer_base::stride()) {
	case sizeof(uint16):
		return renderer::const_index_view_16(
			reinterpret_cast<renderer::const_index_view_16::pointer>(
				detail::index_buffer_base::data()),
			lock_size());
	case sizeof(uint32):
		return renderer::const_index_view_32(
			reinterpret_cast<renderer::const_index_view_32::pointer>(
				detail::index_buffer_base::data()),
			lock_size());
	default:
		throw exception(SGE_TEXT("Invalid stride in ogl::index_buffer::view()!"));
	}	
}
