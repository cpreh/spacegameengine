//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_BUFFERS_VERTEX_COUNT_HPP_INCLUDED
#define SGE_SPRITE_BUFFERS_VERTEX_COUNT_HPP_INCLUDED

#include <sge/renderer/vertex/count.hpp>
#include <sge/sprite/count.hpp>
#include <sge/sprite/geometry/detail/vertices_per_sprite.hpp>


namespace sge
{
namespace sprite
{
namespace buffers
{

template<
	typename Choices
>
inline
sge::renderer::vertex::count
vertex_count(
	sge::sprite::count const _sprites
)
{
	return
		sge::renderer::vertex::count(
			_sprites.get()
			*
			sge::sprite::geometry::detail::vertices_per_sprite<
				Choices
			>::value
		);
}

}
}
}

#endif
