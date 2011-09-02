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


#include "load_function_base.hpp"
#include "object.hpp"
#include <sge/plugin/library/function_map.hpp>
#include <sge/plugin/library/function_base.hpp>
#include <fcppt/config/platform.hpp>

sge::plugin::library::function_base
sge::plugin::library::load_function_base(
	library::object &_object,
	library::symbol_string const &_name
)
{
	char const *const map_name = "sge_plugin_functions";

#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	typedef library::function_map const *(*map_function)();

	return
		reinterpret_cast<
			map_function
		>(
			_object.load(
				map_name
			)
		)()->function(
			_name
		);
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
	return
		static_cast<
			library::function_map *
		>(
			_object.load(
				map_name
			)
		)->function(
			_name
		);
#else
#error "Don't know how to load library functions!"
#endif
}
