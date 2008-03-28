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


#include "../config.h"
#ifdef SGE_LINUX_PLATFORM
#include <cstdlib>
#endif
#include "../client_config.hpp"
#include "../exception.hpp"
#include "../iconv.hpp"

sge::path sge::client_config_path()
{
#ifdef SGE_LINUX_PLATFORM
	const char* const ret = std::getenv("HOME");
	if(!ret)
		throw exception(SGE_TEXT("client_config_path(): Can't find \"HOME\"!"));
	return path(iconv(ret));
#else
	return SGE_TEXT(""); // FIXME
#endif
}
