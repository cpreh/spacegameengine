//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_CONFIG_NORMAL_SIZE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_NORMAL_SIZE_HPP_INCLUDED

#include <sge/sprite/config/normal_size_fwd.hpp> // IWYU pragma: keep
#include <sge/sprite/config/size_choice.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/detail/primitives/normal_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::config
{

template <sge::sprite::config::texture_size_option TextureSize>
struct normal_size final : sge::sprite::config::size_choice
{
  using texture_option =
      std::integral_constant<sge::sprite::config::texture_size_option, TextureSize>;

  template <typename Choices>
  struct apply : sge::sprite::detail::primitives::normal_size<Choices, TextureSize>
  {
  };
};

}

#endif
