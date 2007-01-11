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


#include "../index_buffer.hpp"

sge::ogl::index_buffer::index_buffer(const size_type sz, const resource_flag_t flags, const const_pointer src)
 : basic_arb_buffer<sge::index_buffer,GL_ELEMENT_ARRAY_BUFFER_ARB>(sz,sge::index_buffer::stride,flags,src)
{}

sge::ogl::index_buffer::iterator sge::ogl::index_buffer::begin()
{
	return data();
}

sge::ogl::index_buffer::const_iterator sge::ogl::index_buffer::begin() const
{
	return data();
}
