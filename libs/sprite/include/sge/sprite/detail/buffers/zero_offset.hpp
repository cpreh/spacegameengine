//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_BUFFERS_ZERO_OFFSET_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_BUFFERS_ZERO_OFFSET_HPP_INCLUDED

#include <sge/sprite/buffers/offset_object.hpp>
#include <sge/sprite/buffers/roles/first_index.hpp>
#include <sge/sprite/buffers/roles/first_vertex.hpp>
#include <sge/sprite/detail/config/needs_index_buffer.hpp>
#include <fcppt/not.hpp>
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
inline
std::enable_if_t<
	sge::sprite::detail::config::needs_index_buffer<
		Choices
	>::value,
	sge::sprite::buffers::offset_object<
		Choices
	>
>
zero_offset()
{
	return
		sge::sprite::buffers::offset_object<
			Choices
		>(
			sge::sprite::buffers::roles::first_vertex{} =
				sge::renderer::vertex::first{
					0u
				},
			sge::sprite::buffers::roles::first_index{} =
				sge::renderer::index::first{
					0u
				}
		);
}

template<
	typename Choices
>
inline
std::enable_if_t<
	fcppt::not_(
		sge::sprite::detail::config::needs_index_buffer<
			Choices
		>::value
	),
	sge::sprite::buffers::offset_object<
		Choices
	>
>
zero_offset()
{
	return
		sge::sprite::buffers::offset_object<
			Choices
		>(
			sge::sprite::buffers::roles::first_vertex{} =
				sge::renderer::vertex::first{
					0u
				}
		);
}

}
}
}
}

#endif
