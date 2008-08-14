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


#include <sge/renderer/vertex_view.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

template<typename Vertex>
sge::renderer::basic_vertex_view<Vertex>::basic_vertex_view(
	pointer const raw_data,
	size_type const size_,
	vertex_format const &format_)
: raw_data(raw_data),
  size_(size_),
  format_(format_)
{
	if(!raw_data)
		throw exception(
			SGE_TEXT("vertex_view::data may not be 0!"));
}

template<typename Vertex>
typename sge::renderer::basic_vertex_view<Vertex>::iterator
sge::renderer::basic_vertex_view<Vertex>::begin() const
{
	return iterator(
		data(),
		format().stride(),
		format().offsets());
}

template<typename Vertex>
typename sge::renderer::basic_vertex_view<Vertex>::iterator
sge::renderer::basic_vertex_view<Vertex>::end() const
{
	return begin() + size();
}

template<typename Vertex>
typename sge::renderer::basic_vertex_view<Vertex>::size_type
sge::renderer::basic_vertex_view<Vertex>::size() const
{
	return size_;
}

template<typename Vertex>
sge::renderer::vertex_format const &
sge::renderer::basic_vertex_view<Vertex>::format() const
{
	return format_;
}

template<typename Vertex>
typename sge::renderer::basic_vertex_view<Vertex>::pointer
sge::renderer::basic_vertex_view<Vertex>::data() const
{
	return raw_data;
}

template class sge::renderer::basic_vertex_view<sge::renderer::vertex>;
template class sge::renderer::basic_vertex_view<sge::renderer::const_vertex>;
