/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SYSTEMS_DETAIL_ANY_TYPES_FWD_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_ANY_TYPES_FWD_HPP_INCLUDED

#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/config_fwd.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/detail/input_fwd.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

typedef boost::mpl::vector8<
	sge::systems::config,
	sge::systems::window,
	sge::systems::detail::renderer,
	sge::systems::image2d,
	sge::systems::audio_loader,
	sge::systems::audio_player,
	sge::systems::detail::input,
	sge::systems::font
> any_types;

}
}
}

#endif
