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


#include <sge/config.h>
#include <sge/library/object.hpp>
#include <sge/library/error.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#ifdef SGE_WINDOWS_PLATFORM
#include <sge/windows/windows.hpp>
#elif SGE_POSIX_PLATFORM
#include <sge/iconv.hpp>
#include <sge/funptr_cast.hpp>
#include <dlfcn.h>
#else
#error "Implement me!"
#endif

sge::library::object::object(
	filesystem::path const &nname)
:
#ifdef SGE_WINDOWS_PLATFORM
	handle(reinterpret_cast<void*>(LoadLibrary(nname.string().c_str())))
#elif SGE_POSIX_PLATFORM
	handle(dlopen(iconv(nname.string()).c_str(), RTLD_NOW | RTLD_GLOBAL))
#endif
	, name_(nname)
{
	if(!handle)
		throw exception(
			string(
				SGE_TEXT("failed to load library::object: "))
				+ error());
}

sge::library::object::~object()
{
	if(handle)
	{
#ifdef SGE_WINDOWS_PLATFORM
		FreeLibrary(static_cast<HINSTANCE__*>(handle));
#elif SGE_POSIX_PLATFORM
		dlclose(handle);
#endif
	}
}

sge::filesystem::path const &
sge::library::object::name() const
{
	return name_;
}

sge::library::object::base_fun
sge::library::object::load_address_base(
	std::string const &fun)
{
#ifdef SGE_WINDOWS_PLATFORM
	return reinterpret_cast<base_fun>(
		GetProcAddress(static_cast<HINSTANCE__*>(handle), fun.c_str()));
#elif SGE_POSIX_PLATFORM
	return funptr_cast<base_fun>(
		dlsym(handle, fun.c_str()));
#endif
}
