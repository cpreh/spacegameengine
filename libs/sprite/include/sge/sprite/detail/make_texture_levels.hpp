//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_MAKE_TEXTURE_LEVELS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_MAKE_TEXTURE_LEVELS_HPP_INCLUDED

#include <sge/sprite/texture_level.hpp>
#include <fcppt/metal/interval.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Levels
>
using make_texture_levels
=
fcppt::metal::interval<
	sge::sprite::texture_level,
	0u,
	Levels::value
>;

}
}
}

#endif
