//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RUCKSACK_TESTBED_SYSTEMS_FWD_HPP_INCLUDED
#define SGE_RUCKSACK_TESTBED_SYSTEMS_FWD_HPP_INCLUDED

#include <sge/systems/instance_fwd.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/with_input_fwd.hpp>
#include <sge/systems/with_renderer_fwd.hpp>
#include <sge/systems/with_window_fwd.hpp>


namespace sge
{
namespace rucksack
{
namespace testbed
{

typedef
sge::systems::instance<
	sge::systems::with_window,
	sge::systems::with_renderer<
		sge::systems::renderer_caps::ffp
	>,
	sge::systems::with_input
>
systems;

}
}
}

#endif
