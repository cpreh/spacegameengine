/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/library/object.hpp>
#include <sge/library/error.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config.h>
#ifdef FCPPT_WINDOWS_PLATFORM
#include <sge/windows/windows.hpp>
#include <fcppt/iconv.hpp>
#include <fcppt/auto_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <exception>
#elif FCPPT_POSIX_PLATFORM
#include <fcppt/iconv.hpp>
#include <dlfcn.h>
#else
#error "Implement me!"
#endif

#ifdef FCPPT_WINDOWS_PLATFORM
namespace
{

void
free_library(
	HMODULE const module
)
{
	FreeLibrary(module);
}

struct context
{
	FCPPT_NONCOPYABLE(context);
public:
	explicit context(
		HMODULE const hinst)
	:
		hinst(hinst)
	{}

	~context()
	{
		free_library(hinst);
	}
private:
	HMODULE const hinst;
};

typedef boost::ptr_vector<
	context
> library_vector;

library_vector libraries;

}

struct sge::library::object::destroyer
{
	FCPPT_NONCOPYABLE(destroyer)
public:
	destroyer()
	{
		libraries.clear();
	}
};

#endif

sge::library::object::object(
	fcppt::filesystem::path const &nname
)
:
#ifdef FCPPT_WINDOWS_PLATFORM
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
#elif FCPPT_POSIX_PLATFORM
	handle(
		dlopen(
			fcppt::iconv(
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
			fcppt::string(
				FCPPT_TEXT("failed to load library::object: "))
				+ error()
			);
}

sge::library::object::~object()
{
	if(!handle)
		return;

#ifdef FCPPT_WINDOWS_PLATFORM
	HMODULE const module(
		static_cast<HMODULE>(
			handle
		)
	);

	sge::auto_ptr<
		context
	> ctx(
		new context(
			module
		)
	);

	// NOTE: we can't free the library here,
	// because an exception might be propagating that
	// has been risen from a dll
	// if we destroy the dll here, the catch of
	// exception will crash
	if(std::uncaught_exception())
		libraries.push_back(
			ctx
		);
	else
		free_library(
			module
		);
#elif FCPPT_POSIX_PLATFORM
	dlclose(handle);
#endif
}

fcppt::filesystem::path const &
sge::library::object::name() const
{
	return name_;
}

sge::library::object::base_fun
sge::library::object::load_address_base(
	std::string const &fun)
{
#ifdef FCPPT_WINDOWS_PLATFORM
	FARPROC const ret(
		GetProcAddress(
			static_cast<HMODULE>(handle),
			fun.c_str())
	);

	if(!ret)
		throw exception(
			FCPPT_TEXT("Function ")
			+ fcppt::iconv(fun)
			+ FCPPT_TEXT(" not found in ")
			+ name_.string()
		);

	return reinterpret_cast<base_fun>(
		ret
	);
#elif FCPPT_POSIX_PLATFORM
	dlerror(); // clear last error

	union {
		void *dl_ptr;
		base_fun dl_fun;
	} ret;

	ret.dl_ptr = dlsym(
		handle,
		fun.c_str()
	);

	if(dlerror())
		throw exception(
			fcppt::iconv(fun)
			+ FCPPT_TEXT(" not found in library ")
			+ name().string()
		);

	return ret.dl_fun;
#endif
}
