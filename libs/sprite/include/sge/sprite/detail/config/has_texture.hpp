//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_DETAIL_CONFIG_HAS_TEXTURE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_HAS_TEXTURE_HPP_INCLUDED

#include <sge/sprite/config/is_with_texture.hpp>
#include <sge/sprite/detail/config/contains_if.hpp>


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
using has_texture
=
sge::sprite::detail::config::contains_if<
	typename Choices::optional_elements,
	sge::sprite::config::is_with_texture
>;

}
}
}
}

#endif
