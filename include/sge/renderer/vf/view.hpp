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


#ifndef SGE_RENDERER_VF_VIEW_HPP_INCLUDED
#define SGE_RENDERER_VF_VIEW_HPP_INCLUDED

#include <sge/renderer/vf/dynamic_view.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{

template<typename>
class iterator;

template<
	typename VertexFormat
>
class view {
public:
	typedef vf::iterator<VertexFormat> iterator;
	typedef typename VertexFormat::pointer pointer;
	typedef basic_dynamic_view<pointer> dynamic_view_type;
	typedef vertex_size size_type;

	explicit view(
		dynamic_view_type const &v)
	:
		data(v.data()),
		size(v.size())
	{}
	
	template<typename OtherView>
	explicit view(
		basic_dynamic_view<OtherView> const &v)
	:
		data(v.data()),
		size(v.size())
	{}

	iterator begin() const
	{
		return iterator(
			data);
	}

	iterator end() const
	{
		return iterator(
			data + size);
	}
private:
	pointer   const data;
	size_type const size;
};

}
}
}

#endif
