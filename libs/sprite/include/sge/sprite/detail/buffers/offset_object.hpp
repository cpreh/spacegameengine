/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_BUFFERS_OFFSET_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_BUFFERS_OFFSET_OBJECT_HPP_INCLUDED

#include <sge/renderer/index/first.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/sprite/buffers/roles/first_index.hpp>
#include <sge/sprite/buffers/roles/first_vertex.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace buffers
{

template<
	typename Choices
>
struct offset_object
{
private:
	typedef
	fcppt::record::element<
		sge::sprite::buffers::roles::first_vertex,
		sge::renderer::vertex::first
	>
	vertex_buffer_role;

	typedef
	fcppt::record::element<
		sge::sprite::buffers::roles::first_index,
		sge::renderer::index::first
	>
	index_buffer_role;
public:
	typedef
	fcppt::record::object<
		typename
		boost::mpl::if_<
			sge::sprite::detail::config::needs_index_buffer<
				Choices
			>,
			boost::mpl::vector2<
				vertex_buffer_role,
				index_buffer_role
			>,
			boost::mpl::vector1<
				vertex_buffer_role
			>
		>::type
	>
	type;
};

}
}
}
}

#endif
