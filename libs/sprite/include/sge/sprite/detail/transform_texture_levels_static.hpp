//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_TRANSFORM_TEXTURE_LEVELS_STATIC_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_TRANSFORM_TEXTURE_LEVELS_STATIC_HPP_INCLUDED

#include <sge/sprite/detail/make_texture_levels.hpp>
#include <fcppt/mpl/list/map.hpp>


namespace sge::sprite::detail
{

template<
	typename Function,
	typename Levels
>
using
transform_texture_levels_static
=
fcppt::mpl::list::map<
	sge::sprite::detail::make_texture_levels<
		Levels
	>,
	Function
>;

}

#endif
