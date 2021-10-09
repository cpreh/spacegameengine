//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_STATE_DETAIL_OPTIONS_CLASS_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_OPTIONS_CLASS_HPP_INCLUDED

#include <sge/sprite/state/detail/options_class_impl.hpp>

namespace sge::sprite::state::detail
{

template <typename StateChoices>
using options_class = typename sge::sprite::state::detail::options_class_impl<StateChoices>::type;

}

#endif
