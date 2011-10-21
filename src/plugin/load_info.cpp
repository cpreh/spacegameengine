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


#include "load_info.hpp"
#include "library/object.hpp"
#include "library/load_function.hpp"
#include <sge/plugin/info.hpp>
#include <sge/plugin/library/detail/version_function_name.hpp>


sge::plugin::info const
sge::plugin::load_info(
	fcppt::filesystem::path const &_path
)
{
	typedef sge::plugin::info const
	(*version_function)();

	library::object lib(
		_path
	);

	return
		library::load_function<
			version_function
		>(
			lib,
			plugin::library::detail::version_function_name
		)();
}
