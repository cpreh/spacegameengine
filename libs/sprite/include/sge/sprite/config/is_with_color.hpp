//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_CONFIG_IS_WITH_COLOR_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_IS_WITH_COLOR_HPP_INCLUDED

#include <sge/sprite/config/with_color_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::config
{

template <typename T>
struct is_with_color : std::false_type
{
};

template <typename ColorFormat>
struct is_with_color<sge::sprite::config::with_color<ColorFormat>> : std::true_type
{
};

}

#endif
