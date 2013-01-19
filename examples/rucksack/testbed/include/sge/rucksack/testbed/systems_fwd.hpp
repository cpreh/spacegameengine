/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_RUCKSACK_TESTBED_SYSTEMS_FWD_HPP_INCLUDED
#define SGE_RUCKSACK_TESTBED_SYSTEMS_FWD_HPP_INCLUDED

#include <sge/systems/instance_fwd.hpp>
#include <sge/systems/keyboard_collector_fwd.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/with_input_fwd.hpp>
#include <sge/systems/with_renderer_fwd.hpp>
#include <sge/systems/with_window_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace rucksack
{
namespace testbed
{

typedef sge::systems::instance<
	boost::mpl::vector3<
		sge::systems::with_window,
		sge::systems::with_renderer<
			sge::systems::renderer_caps::ffp
		>,
		sge::systems::with_input<
			boost::mpl::vector1<
				sge::systems::keyboard_collector
			>
		>
	>
> systems;

}
}
}

#endif
