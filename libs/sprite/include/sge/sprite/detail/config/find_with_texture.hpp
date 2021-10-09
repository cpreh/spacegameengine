//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_CONFIG_FIND_WITH_TEXTURE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_FIND_WITH_TEXTURE_HPP_INCLUDED

#include <sge/sprite/config/is_with_texture.hpp>
#include <sge/sprite/detail/config/find_if.hpp>
#include <fcppt/mpl/list/front.hpp>

namespace sge::sprite::detail::config
{

template <typename Choices>
using find_with_texture = fcppt::mpl::list::front<sge::sprite::detail::config::find_if<
    typename Choices::optional_elements,
    sge::sprite::config::is_with_texture>>;

}

#endif
