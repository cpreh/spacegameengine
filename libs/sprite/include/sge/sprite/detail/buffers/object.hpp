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


#ifndef SGE_SPRITE_DETAIL_BUFFERS_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_BUFFERS_OBJECT_HPP_INCLUDED

#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/sprite/buffers/roles/index_buffer.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/if.hpp>
#include <brigand/sequences/list.hpp>
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
struct object
{
private:
	typedef
	fcppt::record::element<
		sge::sprite::buffers::roles::vertex_buffer,
		sge::renderer::vertex::buffer_unique_ptr
	>
	vertex_buffer_role;

	typedef
	fcppt::record::element<
		sge::sprite::buffers::roles::index_buffer,
		sge::renderer::index::buffer_unique_ptr
	>
	index_buffer_role;
public:
	typedef
	fcppt::record::object<
		typename
		brigand::if_<
			sge::sprite::detail::config::needs_index_buffer<
				Choices
			>,
			brigand::list<
				vertex_buffer_role,
				index_buffer_role
			>,
			brigand::list<
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
