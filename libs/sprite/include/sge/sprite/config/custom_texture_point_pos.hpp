//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_CONFIG_CUSTOM_TEXTURE_POINT_POS_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_CUSTOM_TEXTURE_POINT_POS_HPP_INCLUDED

#include <sge/sprite/config/custom_texture_point_pos_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::config
{

template <bool CustomTexturePoint>
struct custom_texture_point_pos
{
  using type = std::integral_constant<bool, CustomTexturePoint>;
};

}

#endif
