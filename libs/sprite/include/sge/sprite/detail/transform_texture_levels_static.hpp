//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_TRANSFORM_TEXTURE_LEVELS_STATIC_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_TRANSFORM_TEXTURE_LEVELS_STATIC_HPP_INCLUDED

#include <sge/sprite/detail/make_texture_levels.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/transform.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Function,
	typename Levels
>
using
transform_texture_levels_static
=
brigand::transform<
	sge::sprite::detail::make_texture_levels<
		Levels
	>,
	Function
>;

}
}
}

#endif
