//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_MAKE_TEXTURE_LEVELS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_MAKE_TEXTURE_LEVELS_HPP_INCLUDED

#include <sge/sprite/texture_level.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/range.hpp>
#include <fcppt/config/external_end.hpp>


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
brigand::range<
	sge::sprite::texture_level,
	0u,
	Levels::value
>;

}
}
}

#endif
