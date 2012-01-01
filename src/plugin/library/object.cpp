/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/plugin/library/exception.hpp>
#include <sge/src/plugin/library/error.hpp>
#include <sge/src/plugin/library/object.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <awl/backends/windows/windows.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
#include <fcppt/to_std_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <dlfcn.h>
#include <fcppt/config/external_end.hpp>
#else
#error "Implement me!"
#endif

#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
namespace
{

void
free_library(
	HMODULE const _handle
)
{
	::FreeLibrary(
		_handle
	);
}

struct context
{
	FCPPT_NONCOPYABLE(
		context
	);
public:
	explicit context(
		HMODULE const _handle
	)
	:
		handle_(_handle)
	{
	}

	~context()
	{
		free_library(
			handle_
		);
	}
private:
	HMODULE const handle_;
};

typedef boost::ptr_vector<
	context
> library_vector;

library_vector libraries;

}

struct sge::plugin::library::object::destroyer
{
	FCPPT_NONCOPYABLE(
		destroyer
	);
public:
	destroyer()
	{
		libraries.clear();
	}
};

#endif

sge::plugin::library::object::object(
	fcppt::filesystem::path const &_name
)
:
	name_(_name),
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	destroyer_(
		fcppt::make_unique_ptr<
			destroyer
		>()
	),
	handle_(
		::LoadLibrary(
			fcppt::filesystem::path_to_string(
				_name
			).c_str()
		)
	)
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
	handle_(
		::dlopen(
			fcppt::to_std_string(
				fcppt::filesystem::path_to_string(
					_name
				)
			).c_str(),
			RTLD_NOW
		)
	)
#endif
{
	if(
		!handle_
	)
		throw sge::plugin::library::exception(
			fcppt::string(
				FCPPT_TEXT("Failed to load library::object: "))
				+ library::error()
			);
}

sge::plugin::library::object::~object()
{
	if(
		!handle_
	)
		return;

#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	// NOTE: we can't free the library here,
	// because an exception might be propagating that
	// has been risen from a dll
	// if we destroy the dll here, the catch of
	// exception will crash
	if(
		std::uncaught_exception()
	)
		fcppt::container::ptr::push_back_unique_ptr(
			libraries,
			fcppt::make_unique_ptr<
				context
			>(
				handle_
			)
		);
	else
		free_library(
			handle_
		);
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
	::dlclose(
		handle_
	);
#endif
}

fcppt::filesystem::path const &
sge::plugin::library::object::name() const
{
	return name_;
}

sge::plugin::library::loaded_symbol
sge::plugin::library::object::load(
	library::symbol_string const &_fun
)
{
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	FARPROC const ret(
		::GetProcAddress(
			handle_,
			_fun.c_str()
		)
	);

	if(
		!ret
	)
		throw sge::plugin::library::exception(
			FCPPT_TEXT("Function ")
			+ fcppt::from_std_string(_fun)
			+ FCPPT_TEXT(" not found in ")
			+ fcppt::filesystem::path_to_string(
				this->name()
			)
		);

	return ret;
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
	::dlerror(); // clear last error

	void *const ret(
		::dlsym(
			handle_,
			_fun.c_str()
		)
	);

	if(
		::dlerror()
		!= 0
	)
		throw sge::plugin::library::exception(
			fcppt::from_std_string(_fun)
			+ FCPPT_TEXT(" not found in library ")
			+ fcppt::filesystem::path_to_string(
				this->name()
			)
		);

	return ret;
#endif
}
