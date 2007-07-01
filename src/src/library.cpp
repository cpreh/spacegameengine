/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <stdexcept>
#include "../types.hpp"
#include "../library.hpp"
#include "../iconv.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include "../win32_conv.hpp"
#endif

#include <iostream>

sge::library::library(const string& n)
 :
#ifdef SGE_WINDOWS_PLATFORM
   handle(LoadLibrary(sge_str_to_win(n).c_str()))
#elif SGE_LINUX_PLATFORM
   handle(dlopen(iconv(n).c_str(),RTLD_NOW | RTLD_GLOBAL))
#endif
  , n(n)
{
	if(!handle)
		throw std::runtime_error(std::string("failed to load library: ") + iconv(name()) + " : " + iconv(liberror()));
}

sge::library::~library()
{
	if(handle)
#ifdef SGE_WINDOWS_PLATFORM
		FreeLibrary(handle);
#elif SGE_LINUX_PLATFORM
		dlclose(handle);
#endif
}

const sge::string& sge::library::name() const
{
	return n;
}

sge::string sge::library::liberror()
{
#ifdef SGE_LINUX_PLATFORM
	return dlerror();
#else
	return "stub: Windows DLL error not implemented!";
#endif
}
