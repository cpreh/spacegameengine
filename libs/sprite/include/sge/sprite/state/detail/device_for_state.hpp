//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_STATE_DETAIL_DEVICE_FOR_STATE_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_DEVICE_FOR_STATE_HPP_INCLUDED

#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace sge::sprite::state::detail
{

template <typename State>
using device_for_state = std::
    conditional_t<State::needs_ffp::value, sge::renderer::device::ffp, sge::renderer::device::core>;

}

#endif
