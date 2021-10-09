//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_CONFIG_TEXTURE_LEVEL_COUNT_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_TEXTURE_LEVEL_COUNT_HPP_INCLUDED

#include <sge/sprite/texture_level.hpp>
#include <sge/sprite/config/texture_level_count_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::config
{

template <sge::sprite::texture_level Count>
struct texture_level_count : std::integral_constant<sge::sprite::texture_level, Count>
{
};

}

#endif
