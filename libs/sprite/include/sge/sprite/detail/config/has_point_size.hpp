//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_CONFIG_HAS_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_HAS_POINT_SIZE_HPP_INCLUDED

#include <sge/sprite/config/is_point_size.hpp>

namespace sge::sprite::detail::config
{

template <typename Choices>
using has_point_size = sge::sprite::config::is_point_size<typename Choices::size_choice>;

}

#endif
