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


#include "../funptr_cast.hpp"
#include "../exception.hpp"

template<typename Fun>
Fun sge::library::load_function(const std::string& fun)
{
#ifdef SGE_WINDOWS_PLATFORM
	Fun ptr = reinterpret_cast<Fun>(GetProcAddress(handle, fun.c_str()));
#elif SGE_LINUX_PLATFORM
	Fun ptr = funptr_cast<Fun>(dlsym(handle, fun.c_str()));
#endif
	if(!ptr)
		throw exception("failed to load function " + fun + " from library " + name() + " : " + liberror());
	return ptr;
}
