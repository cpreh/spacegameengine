//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_CONFIG_UNIT_TYPE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_UNIT_TYPE_HPP_INCLUDED

#include <sge/sprite/config/unit_type_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::config
{

template <typename Type>
struct unit_type
{
  using type = Type;

  static_assert(std::is_arithmetic_v<Type>, "The unit_type must be arithmetic");
};

}

#endif
