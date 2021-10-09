//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_INTRUSIVE_PROCESS_ORDERED_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_PROCESS_ORDERED_HPP_INCLUDED

#include <sge/sprite/intrusive/ordered/collection_fwd.hpp>
#include <sge/sprite/intrusive/process/ordered_with_options.hpp>
#include <sge/sprite/process/default_geometry_options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/options_impl.hpp>
#include <sge/sprite/state/vertex_options.hpp>

namespace sge::sprite::intrusive::process
{

template <
    typename Choices,
    typename Order,
    typename Buffers,
    typename StateChoices,
    typename Compare>
void ordered(
    sge::sprite::intrusive::ordered::collection<Choices, Order> &_collection,
    Buffers &_buffers,
    sge::sprite::state::object<StateChoices> const &_states,
    Compare const &_compare)
{
  sge::sprite::intrusive::process::ordered_with_options<sge::sprite::process::options<
      sge::sprite::process::default_geometry_options<Choices, Compare>::value>>(
      _collection,
      _buffers,
      _states,
      _compare,
      sge::sprite::state::options<StateChoices>(sge::sprite::state::vertex_options::declaration));
}

}

#endif
