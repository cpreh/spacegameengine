/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_AUDIO_PLAYER_PLUGIN_TRAITS_HPP_INCLUDED
#define SGE_AUDIO_PLAYER_PLUGIN_TRAITS_HPP_INCLUDED

#include <sge/audio/player_unique_ptr.hpp>
#include <sge/audio/detail/symbol.hpp>
#include <sge/plugin/capabilities_fwd.hpp>
#include <sge/plugin/detail/address_name.hpp>
#include <sge/plugin/detail/traits.hpp>


namespace sge
{
namespace plugin
{
namespace detail
{

template<>
struct traits<
	sge::audio::player
>
{
public:
	SGE_AUDIO_DETAIL_SYMBOL
	static
	sge::plugin::detail::address_name
	plugin_loader_name();

	SGE_AUDIO_DETAIL_SYMBOL
	static
	sge::plugin::capabilities
	plugin_type();

	using
	loader_function
	=
	sge::audio::player_unique_ptr ();
};

}
}
}

#endif
