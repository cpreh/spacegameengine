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


#include <sge/plugin/info.hpp>
#include <sge/plugin/library/detail/version_function_name.hpp>
#include <sge/src/plugin/load_info.hpp>
#include <sge/src/plugin/library/load_function.hpp>
#include <sge/src/plugin/library/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::plugin::info
sge::plugin::load_info(
	boost::filesystem::path const &_path
)
{
	typedef sge::plugin::info
	(*version_function)();

	sge::plugin::library::object lib(
		_path
	);

	return
		sge::plugin::library::load_function<
			version_function
		>(
			lib,
			sge::plugin::library::detail::version_function_name
		)();
}
