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
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/from_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
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
	using
	vertex_buffer_role
	=
	fcppt::record::element<
		sge::sprite::buffers::roles::first_vertex,
		sge::renderer::vertex::first
	>;

	using
	index_buffer_role
	=
	fcppt::record::element<
		sge::sprite::buffers::roles::first_index,
		sge::renderer::index::first
	>;
public:
	using
	type
	=
	fcppt::record::from_list<
		std::conditional_t<
			sge::sprite::detail::config::needs_index_buffer<
				Choices
			>::value,
			fcppt::mpl::list::object<
				vertex_buffer_role,
				index_buffer_role
			>,
			fcppt::mpl::list::object<
				vertex_buffer_role
			>
		>
	>;
};

}
}
}
}

#endif
