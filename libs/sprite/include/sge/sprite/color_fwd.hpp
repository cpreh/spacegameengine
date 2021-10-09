//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_COLOR_FWD_HPP_INCLUDED
#define SGE_SPRITE_COLOR_FWD_HPP_INCLUDED

#include <sge/image/pixel/mizuiro_type_fwd.hpp>
#include <sge/sprite/detail/config/color_format.hpp>

namespace sge::sprite
{

template <typename Choices>
using color = sge::image::pixel::mizuiro_type<
    typename sge::sprite::detail::config::color_format<Choices>::type>;

}

#endif
