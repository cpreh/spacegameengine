//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_CONFIG_POS_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_POS_HPP_INCLUDED

#include <sge/sprite/config/pos_choice.hpp>
#include <sge/sprite/config/pos_fwd.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/detail/primitives/pos.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::config
{

template <sge::sprite::config::pos_option Option>
struct pos final : sge::sprite::config::pos_choice
{
  using option = std::integral_constant<sge::sprite::config::pos_option, Option>;

  template <typename Choices>
  struct apply : sge::sprite::detail::primitives::pos<Choices, Option>
  {
  };
};

}

#endif
