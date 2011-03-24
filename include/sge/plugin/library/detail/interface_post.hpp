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


#ifndef SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_POST_HPP_INCLUDED
#define SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_POST_HPP_INCLUDED

#include <fcppt/platform.hpp>

#if defined(FCPPT_POSIX_PLATFORM)

#define SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_POST \
);\
}

#elif defined(FCPPT_WINDOWS_PLATFORM)

#include <sge/plugin/library/function_map.hpp>
#include <fcppt/export_symbol.hpp>

#define SGE_PLUGIN_LIBRARY_DETAIL_INTERFACE_POST \
	);\
}\
extern "C" \
{ \
FCPPT_EXPORT_SYMBOL \
sge::plugin::library::function_map const * \
sge_plugin_functions() \
{\
	return &sge_plugin_functions_global;\
}\
}

#else
#error "Don't know what the library interface should look like!"
#endif

#endif
