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


#include <sge/config/plugin_path.hpp>
#include <sge/build/plugin_path.hpp>
#include <fcppt/from_std_string.hpp>

fcppt::filesystem::path const
sge::config::plugin_path()
{
	return
		sge::build_plugin_path()
// VC++ puts the binaries inside ${LIBRARY_OUTPUT_PATH}/Release or Debug
#if defined(SGE_CONFIG_LOCAL_BUILD) && defined(_MSC_VER)
		/
		fcppt::from_std_string(
			CMAKE_INTDIR
		)
#endif
		;
}
