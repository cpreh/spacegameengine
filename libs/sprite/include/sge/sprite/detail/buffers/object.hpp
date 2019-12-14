//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_BUFFERS_OBJECT_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_BUFFERS_OBJECT_HPP_INCLUDED

#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/sprite/buffers/roles/index_buffer.hpp>
#include <sge/sprite/buffers/roles/vertex_buffer.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/from_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
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
	fcppt::record::from_list<
		std::conditional_t<
			sge::sprite::detail::config::needs_index_buffer<
				Choices
			>::value,
			metal::list<
				vertex_buffer_role,
				index_buffer_role
			>,
			metal::list<
				vertex_buffer_role
			>
		>
	>
	type;
};

}
}
}
}

#endif
