//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/player.hpp>
#include <sge/audio/player_plugin/traits.hpp> // NOLINT(misc-include-cleaner)
#include <sge/plugin/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/systems/impl/plugin_pair_impl.hpp>
#include <sge/systems/impl/audio/player_pair.hpp> // NOLINT(misc-include-cleaner)

template class sge::systems::impl::plugin_pair<sge::audio::player>;
