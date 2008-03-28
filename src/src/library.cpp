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
#include "../exception.hpp"
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

sge::library::library(const path& nname)
 :
#ifdef SGE_WINDOWS_PLATFORM
  handle(reinterpret_cast<void*>(LoadLibrary(nname.string().c_str())))
#elif SGE_LINUX_PLATFORM
   handle(dlopen(iconv(nname.string()).c_str(), RTLD_NOW | RTLD_GLOBAL))
#endif
  , name_(nname)
{
	if(!handle)
		throw exception(string(SGE_TEXT("failed to load library: ")) + name().string() + SGE_TEXT(" : ") + liberror());
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

const sge::path& sge::library::name() const
{
	return name_;
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

sge::string sge::library::liberror()
{
#ifdef SGE_LINUX_PLATFORM
	return iconv(dlerror());
#else
	const DWORD lasterror = GetLastError();
	boost::array<string::value_type, 256> errmsg;
	if(FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM,
		0, // ignored
		lasterror, // message id
		0, // language id
		errmsg.c_array(),
		errmsg.size()-1,
		0
	) == 0)
		return string(SGE_TEXT("FormatMessage() failed!"));
	return string(errmsg.data());
#endif
}

sge::library::load_function_exception::load_function_exception(const string &lib, const std::string &fun)
: exception(SGE_TEXT("Failed to load function ") + iconv(fun) + SGE_TEXT(" from library ") + lib + SGE_TEXT(" : ") + liberror()),
  lib(lib),
  func(fun)
{}
