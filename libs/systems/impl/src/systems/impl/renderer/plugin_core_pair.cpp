//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/plugin/object.hpp>
#include <sge/renderer/core.hpp>
#include <sge/renderer/plugin/traits.hpp>
#include <sge/systems/impl/plugin_pair_impl.hpp>
#include <sge/systems/impl/renderer/plugin_core_pair.hpp>


template
class
sge::systems::impl::plugin_pair<
	sge::renderer::core
>;
