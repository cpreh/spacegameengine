//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_HAS_TEXTURE_COORDINATES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_HAS_TEXTURE_COORDINATES_HPP_INCLUDED

#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/detail/config/find_with_texture.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
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
using has_texture_coordinates
=
std::integral_constant<
	bool,
	sge::sprite::detail::config::find_with_texture<
		Choices
	>::coordinates::value
	==
	sge::sprite::config::texture_coordinates::custom
>;

}
}
}
}

#endif
