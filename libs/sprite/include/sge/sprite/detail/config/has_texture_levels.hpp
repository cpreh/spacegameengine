//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_HAS_TEXTURE_LEVELS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_HAS_TEXTURE_LEVELS_HPP_INCLUDED

#include <sge/sprite/detail/config/has_texture.hpp>
#include <sge/sprite/detail/config/has_texture_point_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/logical/or.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace config
{

template<
	typename Choices
>
using has_texture_levels
=
brigand::or_<
	sge::sprite::detail::config::has_texture<
		Choices
	>,
	sge::sprite::detail::config::has_texture_point_size<
		Choices
	>
>;

}
}
}
}

#endif
