//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_CONFIG_HAS_CUSTOM_TEXTURE_POINT_POS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_HAS_CUSTOM_TEXTURE_POINT_POS_HPP_INCLUDED

#include <sge/sprite/detail/config/find_with_texture_point_size.hpp>

namespace sge::sprite::detail::config
{

template <typename Choices>
using has_custom_texture_point_pos =
    typename sge::sprite::detail::config::find_with_texture_point_size<Choices>::point_pos::type;

}

#endif
