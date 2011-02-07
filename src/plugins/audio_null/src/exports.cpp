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


#include "../player.hpp"
#include <sge/plugin/info.hpp>
#include <fcppt/export_symbol.hpp>
#include <fcppt/text.hpp>

namespace
{

sge::plugin::info const info(
	FCPPT_TEXT("audionull"),
	FCPPT_TEXT("audio plugin that does not do anything"),
	sge::plugin::version(0x1),
	sge::plugin::min_core_version(0x1)
	sge::plugin::capabilities::audio_player
);

sge::audio::player_ptr const
create_audio_player()
{
	return
		fcppt::make_shared_ptr<
			sge::audio_null::player
		>();
}

}

#if defined(FCPPT_POSIX_PLATFORM)
#define SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(\
	function_map,\
	info\
)\
extern "C" \
{\
	FCPPT_EXPORT_SYMBOL \
	sge::plugin::function_map sge_plugin_functions(\
		function_map\
	);\
}

#elif defined(FCPPT_WINDOWS_PLATFORM)

#define SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(\
	function_map,\
	info\
)\
extern "C" \
{ \
	FCPPT_EXPORT_SYMBOL \
	sge::plugin::library::function_map const \
	load_function_map()\
	{\
		return function_map;\
	}\
#else
#error "Don't know how to load functions from plugins!"
#endif

SGE_PLUGIN_LIBRARY_MAKE_INTERFACE(
