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
	const size_type size,
	const renderer::vertex_format& format,
	const resource_flag_type flags,
	const const_pointer src)
 :	detail::vertex_buffer_base(
 		size,
		format.stride(),
		flags,
		src),
	format(format),
	ogl_format(format)
{}

sge::ogl::vertex_buffer::size_type
sge::ogl::vertex_buffer::stride() const
{
	return format.stride();
}

const sge::renderer::vertex_format&
sge::ogl::vertex_buffer::get_vertex_format() const
{
	return format;
}

/*sge::ogl::vertex_buffer::iterator
sge::ogl::vertex_buffer::create_iterator(
	const pointer p)
{
	return iterator(
		p,
		format.stride(),
		ogl_format.offsets());
}

sge::ogl::vertex_buffer::const_iterator
sge::ogl::vertex_buffer::create_iterator(
	const const_pointer p) const
{
	return const_iterator(
		p,
		stride(),
		ogl_format.offsets());
}*/

void sge::ogl::vertex_buffer::set_format()
{
	bind_me();
	ogl_format.use_me();
}
