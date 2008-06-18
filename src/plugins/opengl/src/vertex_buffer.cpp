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


#include "../vertex_buffer.hpp"
#include "../basic_buffer_impl.hpp"
#include "../vbo.hpp"

template class sge::ogl::basic_buffer<
	sge::renderer::vertex_buffer,
	sge::ogl::vertex_buffer_type,
	sge::ogl::vb_ib_vbo_impl>;

sge::ogl::vertex_buffer::vertex_buffer(
	renderer::const_vertex_view const &src,
	resource_flag_type const flags)
 :	detail::vertex_buffer_base(
 		src.size(),
		src.format().stride(),
		flags,
		src.data()),
	format(src.format()),
	ogl_format(format)
{}

void sge::ogl::vertex_buffer::set_format()
{
	bind_me();
	ogl_format.use_me();
}

void sge::ogl::vertex_buffer::data(
	renderer::const_vertex_view const &src)
{
	detail::vertex_buffer_base::data(
		src.data(),
		src.format().stride(),
		src.size());
}

void sge::ogl::vertex_buffer::do_sub_data(
	renderer::const_vertex_view const &src,
	size_type const first)
{
	detail::vertex_buffer_base::sub_data(
		src.data(),
		first,
		src.size());
}

sge::renderer::vertex_view const
sge::ogl::vertex_buffer::view()
{
	return renderer::vertex_view(
		detail::vertex_buffer_base::data(),
		detail::vertex_buffer_base::lock_size(),
		get_vertex_format());
}

sge::renderer::const_vertex_view const
sge::ogl::vertex_buffer::view() const
{
	return renderer::const_vertex_view(
		detail::vertex_buffer_base::data(),
		detail::vertex_buffer_base::lock_size(),
		get_vertex_format());
}

const sge::renderer::vertex_format&
sge::ogl::vertex_buffer::get_vertex_format() const
{
	return format;
}
