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


#ifndef SGE_RENDERER_VERTEX_VIEW_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_VIEW_HPP_INCLUDED

#include "vertex.hpp"
#include "vertex_iterator.hpp"

namespace sge
{
namespace renderer
{

class vertex_format;

template<typename Vertex>
class basic_vertex_view {
public:
	typedef vertex_size size_type;
	typedef typename Vertex::pointer pointer;
	typedef vb_detail::iterator_impl<Vertex> iterator;

	basic_vertex_view(
		pointer data,
		size_type size,
		vertex_format const &);

	iterator begin() const;
	iterator end() const;
	size_type size() const;
	vertex_format const &format() const;
	pointer data() const;
private:
	pointer       raw_data;
	size_type     size_;
	vertex_format format_;
};

typedef basic_vertex_view<vertex> vertex_view;
typedef basic_vertex_view<const_vertex> const_vertex_view;

}
}

#endif
