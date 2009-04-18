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


#include <sge/config/files.hpp>
#include <sge/config/homedir.hpp>
#include <sge/text.hpp>
#include <sge/config.h>
#ifdef SGE_WINDOWS_PLATFORM
#include <sge/config/appdir.hpp>
#endif
#include <boost/assign/list_of.hpp>

sge::config::path_vector const
sge::config::files()
{
#ifdef SGE_WINDOWS_PLATFORM
	return boost::assign::list_of(
		appdir() / SGE_TEXT("config.txt"),
		homedir() / SGE_TEXT("spacegameengine.txt")
	);
#elif SGE_POSIX_PLATFORM
	return boost::assign::list_of
		(homedir() / SGE_TEXT(".spacegameengine.conf"))
		(filesystem::path(
			SGE_TEXT("/etc")
		) / SGE_TEXT("spacegameengine.conf")
	);
#endif
}
