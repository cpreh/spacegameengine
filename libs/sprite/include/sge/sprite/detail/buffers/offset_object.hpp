//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
