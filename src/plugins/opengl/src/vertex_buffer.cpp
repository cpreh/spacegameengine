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
#include "../vbo.hpp"
#include "../instantiate_buffer_base.hpp"

SGE_OPENGL_INSTANTIATE_BUFFER_BASE(
	sge::renderer::vertex_buffer,
	sge::ogl::vertex_buffer_type,
	sge::ogl::vb_ib_vbo_impl)

sge::ogl::vertex_buffer::vertex_buffer(
	renderer::vertex_format const &format,
	size_type const sz,
	resource_flag_type const flags)
: detail::vertex_buffer_base(
	sz,
	format.stride(),
	flags,
	0),
  format(format),
  ogl_format(format)
{}

void sge::ogl::vertex_buffer::set_format()
{
	bind_me();
	ogl_format.use_me();
}

sge::ogl::vertex_buffer::view_type const
sge::ogl::vertex_buffer::view()
{
	return view_type(
		detail::vertex_buffer_base::data(),
		detail::vertex_buffer_base::lock_size(),
		get_vertex_format());
}

sge::ogl::vertex_buffer::const_view_type const
sge::ogl::vertex_buffer::view() const
{
	return const_view_type(
		detail::vertex_buffer_base::data(),
		detail::vertex_buffer_base::lock_size(),
		get_vertex_format());
}

sge::renderer::vertex_format const &
sge::ogl::vertex_buffer::get_vertex_format() const
{
	return format;
}
