/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "../vertex_buffer.hpp"

sge::ogl::vertex_buffer::vertex_buffer(const size_type size, const sge::vertex_format& format, const resource_flag_t flags, const const_pointer src)
 : base(size,format.stride(),flags,src),
   format(format),
   ogl_format(format)
{}
		
sge::ogl::vertex_buffer::size_type sge::ogl::vertex_buffer::stride() const
{
	return format.stride();
}

const sge::vertex_format& sge::ogl::vertex_buffer::get_vertex_format() const
{
	return format;
}

sge::ogl::vertex_buffer::iterator sge::ogl::vertex_buffer::create_iterator(const pointer p)
{
	return iterator(p,format.stride(),ogl_format.offsets());
}

sge::ogl::vertex_buffer::const_iterator sge::ogl::vertex_buffer::create_iterator(const const_pointer p) const
{
	return const_iterator(p,stride(),ogl_format.offsets());
}

sge::ogl::vertex_buffer::iterator sge::ogl::vertex_buffer::begin()
{
	this->check_lock();
	return create_iterator(data());
}

sge::ogl::vertex_buffer::const_iterator sge::ogl::vertex_buffer::begin() const
{
	this->check_lock();
	return create_iterator(data());
}

void sge::ogl::vertex_buffer::set_format()
{
	bind_me();
	ogl_format.use_me();
}

void sge::ogl::vertex_buffer::unbind()
{
	base::unbind();
}
