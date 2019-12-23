//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_TEXTURE_LEVELS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_TEXTURE_LEVELS_HPP_INCLUDED

#include <sge/sprite/detail/config/find_texture_config.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
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
using
texture_levels
=
typename
metal::front<
	typename
	sge::sprite::detail::config::find_texture_config<
		Choices
	>::type
>::texture_levels;

}
}
}
}

#endif
