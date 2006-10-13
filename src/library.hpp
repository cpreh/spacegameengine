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


#ifndef SGE_LIBRARY_HPP_INCLUDED
#define SGE_LIBRARY_HPP_INCLUDED

#include <string>
#include <stdexcept>
#include <iostream>
#include "./types.hpp"
#include "./bitwise_cast.hpp"

#ifdef SGE_WINDOWS_PLATFORM
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#elif SGE_LINUX_PLATFORM
	#include<dlfcn.h>
#endif

namespace {
	inline const char* liberror()
	{
#ifdef SGE_LINUX_PLATFORM
		return dlerror();
#else
		return "";
#endif
	}
}

namespace sge
{

class library {
private:
#ifdef SGE_WINDOWS_PLATFORM
	HMODULE handle;
#elif SGE_LINUX_PLATFORM
	void* handle;
#endif
public:
	library(const std::string& n)
		:
#ifdef SGE_WINDOWS_PLATFORM
		handle(LoadLibrary(n.c_str()))
#elif SGE_LINUX_PLATFORM
		handle(dlopen(n.c_str(),RTLD_NOW | RTLD_GLOBAL))
#endif
		, n(n)
	{
		if(!handle)
			throw std::runtime_error(std::string("failed to load library: ") + name() + " : " + liberror());
	}

	~library()
	{
		if(handle)
#ifdef SGE_WINDOWS_PLATFORM
			FreeLibrary(handle);
#elif SGE_LINUX_PLATFORM
			dlclose(handle);
#endif
	}

	template<typename Fun>
	Fun load_function(const std::string& fun)
	{
#ifdef SGE_WINDOWS_PLATFORM
		Fun ptr = reinterpret_cast<Fun>(GetProcAddress(handle,fun.c_str()));
#elif SGE_LINUX_PLATFORM
		Fun ptr = bitwise_cast<Fun>(dlsym(handle,fun.c_str()));
#endif
		if(!ptr)
			throw std::runtime_error(std::string("failed to load function ") + fun + " from library " + name() + " : " + liberror());
		return ptr;
	}

	const std::string& name() const { return n; }
private:
	std::string n;
};

}

#endif
