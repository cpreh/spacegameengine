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


#ifndef SGE_AUDIO_PLAYER_PLUGIN_HPP_INCLUDED
#define SGE_AUDIO_PLAYER_PLUGIN_HPP_INCLUDED

#include <sge/audio/player_ptr.hpp>
#include <sge/plugin/detail/traits.hpp>
#include <sge/plugin/detail/address_name.hpp>
#include <sge/plugin/capabilities.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace plugin
{
namespace detail
{

template<>
struct traits<
	audio::player
>
{
public:
	SGE_SYMBOL static address_name
	plugin_loader_name();

	SGE_SYMBOL static capabilities::type
	plugin_type();

	typedef audio::player_ptr const (*loader_fun)();
};

}
}
}

#endif
