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
#include <sge/iconv.hpp>
#include <sge/auto_ptr.hpp>
#include <sge/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>
#elif SGE_POSIX_PLATFORM
#include <sge/iconv.hpp>
#include <sge/funptr_cast.hpp>
#include <dlfcn.h>
#else
#error "Implement me!"
#endif

#ifdef SGE_WINDOWS_PLATFORM
namespace {

struct context {
	SGE_NONCOPYABLE(context);
public:
	explicit context(
		HMODULE const hinst)
	:
		hinst(hinst)
	{}

	~context()
	{
		FreeLibrary(hinst);
	}
private:
	HMODULE const hinst;
};

typedef boost::ptr_vector<
	context
> library_vector;

library_vector libraries;

}

struct sge::library::object::destroyer {
	SGE_NONCOPYABLE(destroyer)
public:
	destroyer()
	{
		libraries.clear();
	}
};

#endif

sge::library::object::object(
	filesystem::path const &nname)
:
#ifdef SGE_WINDOWS_PLATFORM
	destroyer_(
		new destroyer()
	),
	handle(
		static_cast<void*>(
			LoadLibrary(
				nname.string().c_str()
			)
		)
	)
#elif SGE_POSIX_PLATFORM
	handle(
		dlopen(
			iconv(
				nname.string()
			).c_str(),
			RTLD_NOW | RTLD_GLOBAL
		)
	)
#endif
	, name_(nname)
{
	if(!handle)
		throw exception(
			string(
				SGE_TEXT("failed to load library::object: "))
				+ error()
			);
}

sge::library::object::~object()
{
	if(!handle)
		return;

#ifdef SGE_WINDOWS_PLATFORM
	sge::auto_ptr<
		context
	> ctx(
		new context(
			static_cast<HMODULE>(handle)
		)
	);

	// NOTE: we can't free the library here,
	// because an exception might be propagating that
	// has been risen from a dll
	// if the destroy the dll here, the catch of
	// exception will crash
	libraries.push_back(
		ctx
	);
#elif SGE_POSIX_PLATFORM
	dlclose(handle);
#endif
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
	FARPROC const ret(
		GetProcAddress(
			static_cast<HMODULE>(handle),
			fun.c_str())
	);

	if(!ret)
		throw exception(
			SGE_TEXT("Function ")
			+ sge::iconv(fun)
			+ SGE_TEXT(" not found in ")
			+ name_.string()
		);

	return reinterpret_cast<base_fun>(
		ret
	);
#elif SGE_POSIX_PLATFORM
	// TODO: error handling!
	return funptr_cast<base_fun>(
		dlsym(
			handle,
			fun.c_str()
		)
	);
#endif
}
