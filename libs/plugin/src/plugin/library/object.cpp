/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/plugin/library/symbol_string.hpp>
#include <sge/plugin/impl/library/error.hpp>
#include <sge/plugin/impl/library/object.hpp>
#include <fcppt/config/platform.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>

#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
#include <awl/backends/windows/windows.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <vector>
#include <fcppt/config/external_end.hpp>
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
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
	explicit
	context(
		HMODULE const _handle
	)
	:
		handle_(
			_handle
		)
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

typedef
fcppt::unique_ptr<
	context
>
context_unique_ptr;

typedef
std::vector<
	context_unique_ptr
>
library_vector;

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
	boost::filesystem::path const &_name
)
:
	name_(
		_name
	),
#if defined(FCPPT_CONFIG_WINDOWS_PLATFORM)
	handle_(
		::LoadLibrary(
			fcppt::filesystem::path_to_string(
				_name
			).c_str()
		)
	),
	destroyer_(
		fcppt::make_unique_ptr<
			destroyer
		>()
	)
#elif defined(FCPPT_CONFIG_POSIX_PLATFORM)
	handle_(
		::dlopen(
			_name.string().c_str(),
			RTLD_NOW
		)
	)
#endif
{
	if(
		!handle_
	)
		throw
			sge::plugin::library::exception{
				fcppt::string(
					FCPPT_TEXT("Failed to load library::object: ")
					+
					sge::plugin::impl::library::error()
				)
			};
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
		libraries.push_back(
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

boost::filesystem::path const &
sge::plugin::library::object::name() const
{
	return
		name_;
}

sge::plugin::impl::library::loaded_symbol
sge::plugin::library::object::load(
	sge::plugin::library::symbol_string const &_fun
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
		throw
			sge::plugin::library::exception{
				FCPPT_TEXT("Function ")
				+
				fcppt::from_std_string(
					_fun
				)
				+
				FCPPT_TEXT(" not found in ")
				+
				fcppt::filesystem::path_to_string(
					this->name()
				)
			};

	return
		ret;
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
		!=
		nullptr
	)
		throw
			sge::plugin::library::exception{
				fcppt::from_std_string(
					_fun
				)
				+
				FCPPT_TEXT(" not found in library ")
				+
				fcppt::filesystem::path_to_string(
					this->name()
				)
			};

	return
		ret;
#endif
}
