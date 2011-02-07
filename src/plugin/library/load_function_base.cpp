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
#include <fcppt/config.hpp>

sge::plugin::library::function_base
sge::plugin::library::load_function_base(
	library::object &_object,
	library::symbol_string const &_name
)
{
	char const *const function_name = "sge_plugin_functions";

#if defined(FCPPT_WINDOWS_PLATFORM)
	
	library::function_map const *const map(
		reinterpret_cast<
			library::function_base
		>(
			_object.load(
				function_name
			)
		)
	);
#elif defined(FCPPT_POSIX_PLATFORM)
	return
		static_cast<
			library::function_map *
		>(
			_object.load(
				"sge_plugin_functions"
			)
		)->functions(
			_name
		);
#else
#error "Don't know how to load library functions!"
#endif
}
