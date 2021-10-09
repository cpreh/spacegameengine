//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_CONFIG_NEEDS_USE_CENTER_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_NEEDS_USE_CENTER_HPP_INCLUDED

#include <sge/sprite/detail/config/has_normal_size.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{
namespace config
{

template <typename Choices>
using needs_use_center = sge::sprite::detail::config::has_normal_size<Choices>;

}
}
}
}

#endif
