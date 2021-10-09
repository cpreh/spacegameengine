//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_STATE_RENDER_CONTEXT_HPP_INCLUDED
#define SGE_SPRITE_STATE_RENDER_CONTEXT_HPP_INCLUDED

#include <sge/renderer/context/core_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/sprite/state/detail/choose_ffp.hpp>

namespace sge::sprite::state
{

template <typename StateChoices>
using render_context = sge::sprite::state::detail::
    choose_ffp<StateChoices, sge::renderer::context::ffp, sge::renderer::context::core>;

}

#endif
