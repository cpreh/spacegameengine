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


#include <sge/renderer/index_buffer.hpp>

// FIXME: do this with fragments

sge::renderer::index_buffer::iterator sge::renderer::index_buffer::end()
{
	return begin() + size();
}

sge::renderer::index_buffer::const_iterator sge::renderer::index_buffer::end() const
{
	return begin() + size();
}

sge::renderer::index_buffer::reverse_iterator sge::renderer::index_buffer::rbegin()
{
	return reverse_iterator(end());
}

sge::renderer::index_buffer::const_reverse_iterator sge::renderer::index_buffer::rbegin() const
{
	return const_reverse_iterator(end());
}

sge::renderer::index_buffer::reverse_iterator sge::renderer::index_buffer::rend()
{
	return reverse_iterator(begin());
}

sge::renderer::index_buffer::const_reverse_iterator sge::renderer::index_buffer::rend() const
{
	return const_reverse_iterator(begin());
}

sge::renderer::index_buffer::reference sge::renderer::index_buffer::operator[](const size_type i)
{
	return *(begin() + i);
}

sge::renderer::index_buffer::const_reference sge::renderer::index_buffer::operator[](const size_type i) const
{
	return *(begin() + i);
}
	
sge::renderer::index_buffer::~index_buffer()
{}
