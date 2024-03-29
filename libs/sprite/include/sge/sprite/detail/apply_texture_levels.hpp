//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_APPLY_TEXTURE_LEVELS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_APPLY_TEXTURE_LEVELS_HPP_INCLUDED

#include <sge/sprite/config/is_texture_level_count.hpp>
#include <sge/sprite/detail/make_texture_levels.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp> // IWYU pragma: keep

namespace sge::sprite::detail
{

template <typename Levels, typename Function>
inline void apply_texture_levels(Function const &_function)
  requires(sge::sprite::config::is_texture_level_count<Levels>::value)
{
  fcppt::algorithm::loop(sge::sprite::detail::make_texture_levels<Levels>{}, _function);
}
}

#endif
