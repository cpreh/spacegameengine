//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_STATE_DEFAULT_OPTIONS_HPP_INCLUDED
#define SGE_SPRITE_STATE_DEFAULT_OPTIONS_HPP_INCLUDED

#include <sge/sprite/state/options_impl.hpp>
#include <sge/sprite/state/vertex_options.hpp>

namespace sge::sprite::state
{

template <typename StateChoices>
sge::sprite::state::options<StateChoices> default_options()
{
  return sge::sprite::state::options<StateChoices>(
      sge::sprite::state::vertex_options::declaration_and_buffer);
}

}

#endif
