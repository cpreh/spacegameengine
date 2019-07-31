//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_GEOMETRY_DETAIL_INDEX_ARRAY_TYPE_HPP_INCLUDED
#define SGE_SPRITE_GEOMETRY_DETAIL_INDEX_ARRAY_TYPE_HPP_INCLUDED

#include <sge/sprite/geometry/detail/indices_per_sprite.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace geometry
{
namespace detail
{

template<
	typename Choices
>
using
index_array_type
=
std::array<
	unsigned,
	sge::sprite::geometry::detail::indices_per_sprite<
		Choices
	>::value
>;

}
}
}
}

#endif
