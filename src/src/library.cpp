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


#include "../exception.hpp"
#include "../types.hpp"
#include "../library.hpp"
#include "../iconv.hpp"
#include "../funptr_cast.hpp"
#ifdef SGE_WINDOWS_PLATFORM
#include <boost/array.hpp>
#include "../win32_conv.hpp"
#include "../windows.hpp"
#elif SGE_LINUX_PLATFORM
#include <dlfcn.h>
#endif

sge::library::library(const std::string& n)
 :
#ifdef SGE_WINDOWS_PLATFORM
  handle(reinterpret_cast<void*>(LoadLibraryA(n.c_str()))) // FIXME: what to do about this?
#elif SGE_LINUX_PLATFORM
   handle(dlopen(n.c_str(), RTLD_NOW | RTLD_GLOBAL))
#endif
  , n(n)
{
	if(!handle)
		throw sge::exception(std::string("failed to load library: ") + name() + " : " + liberror());
}

sge::library::~library()
{
	if(handle)
	{
#ifdef SGE_WINDOWS_PLATFORM
		FreeLibrary(static_cast<HINSTANCE__*>(handle));
#elif SGE_LINUX_PLATFORM
		dlclose(handle);
#endif
	}
}

const std::string& sge::library::name() const
{
	return n;
}

sge::library::base_fun sge::library::load_address_base(const std::string& fun)
{
	return funptr_cast<base_fun>(
#ifdef SGE_WINDOWS_PLATFORM
		GetProcAddress(static_cast<HINSTANCE__*>(handle), fun.c_str())
#elif SGE_LINUX_PLATFORM
		dlsym(handle, fun.c_str())
#endif
	);
}

std::string sge::library::liberror()
{
#ifdef SGE_LINUX_PLATFORM
	return dlerror();
#else
	const DWORD lasterror = GetLastError();
	boost::array<char, 256> errmsg;
	FormatMessageA(
		FORMAT_MESSAGE_FROM_SYSTEM,
		0, // ignored
		lasterror, // message id
		0, // language id
		errmsg.c_array(), // buffer
		errmsg.size()-1, // buffer length
		0
	);
	return std::string(errmsg.data());
#endif
}

//#ifdef SGE_WINDOWS_PLATFORM
//DWORD sge::library::lasterror = 0;
//#endif
