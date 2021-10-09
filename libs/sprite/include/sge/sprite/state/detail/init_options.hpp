//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_STATE_DETAIL_INIT_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_INIT_OPTIONS_HPP_INCLUDED

#include <sge/sprite/state/detail/init_one_option.hpp>
#include <sge/sprite/state/detail/options_class.hpp>
#include <fcppt/record/init.hpp>

namespace sge::sprite::state::detail
{

template <typename StateChoices>
inline sge::sprite::state::detail::options_class<StateChoices> init_options()
{
  return fcppt::record::init<sge::sprite::state::detail::options_class<StateChoices>>(
      sge::sprite::state::detail::init_one_option<StateChoices>());
}

}

#endif
