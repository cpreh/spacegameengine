/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/audio/player/player.hpp>
#include <sge/plugin/detail/instantiate_types.hpp>

sge::audio::player::~player()
{}

sge::plugin::detail::address_name
sge::plugin::detail::traits<sge::audio::player>::plugin_loader_name()
{
	return SGE_ADDRESS_NAME("create_audio_player");
}

sge::plugin::capabilities::type
sge::plugin::detail::traits<sge::audio::player>::get_plugin_type()
{
	return capabilities::audio_player;
}

SGE_PLUGIN_INSTANTIATE_TYPES(sge::audio::player)
