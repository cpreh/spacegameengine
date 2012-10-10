/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_WITH_RENDERER_HPP_INCLUDED
#define SGE_SYSTEMS_WITH_RENDERER_HPP_INCLUDED

#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/renderer_fwd.hpp>
#include <sge/systems/with_renderer_fwd.hpp>
#include <sge/systems/with_window_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

template<
	sge::systems::renderer_caps::type Caps
>
struct with_renderer
{
	typedef boost::mpl::integral_c<
		sge::systems::renderer_caps::type,
		Caps
	> caps;

	typedef boost::mpl::true_ needs_init;

	typedef sge::systems::renderer parameter_type;

	typedef boost::mpl::vector1<
		sge::systems::with_window
	> needs_before;
};

}
}

#endif
