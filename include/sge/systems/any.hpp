/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_ANY_HPP_INCLUDED
#define SGE_SYSTEMS_ANY_HPP_INCLUDED

#include <sge/systems/audio_loader.hpp>
#include <sge/systems/audio_player.hpp>
#include <sge/systems/basic_loader.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/parameterless.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/window.hpp>
#include <fcppt/variant/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

typedef fcppt::variant::object<
	boost::mpl::vector8<
		systems::config,
		systems::window,
		systems::renderer,
		systems::image2d,
		systems::audio_loader,
		systems::audio_player,
		systems::input,
		systems::parameterless::type
	>
> any;

}
}

#endif
