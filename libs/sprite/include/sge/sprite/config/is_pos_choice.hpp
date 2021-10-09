//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_CONFIG_IS_POS_CHOICE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_IS_POS_CHOICE_HPP_INCLUDED

#include <sge/sprite/config/pos_choice.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::config
{

template <typename T>
using is_pos_choice = std::is_base_of<sge::sprite::config::pos_choice, T>;

}

#endif
