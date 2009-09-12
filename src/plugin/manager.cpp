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


#include "version_fun.hpp"
#include <sge/config.h>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/log/headers.hpp>
#include <sge/library/function_not_found.hpp>
#include <sge/filesystem/directory_iterator.hpp>
#include <sge/filesystem/is_directory.hpp>
#include <sge/filesystem/extension.hpp>
#include <sge/config/plugin_path.hpp>
#include <sge/iconv.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::char_type const *const plugin_extension =
#ifdef SGE_DARWIN_PLATFORM
	SGE_TEXT(".dylib")
#elif SGE_POSIX_PLATFORM
	SGE_TEXT(".so")
#elif SGE_WINDOWS_PLATFORM
	SGE_TEXT(".dll")
#else
#error "Don't know which plugin extension to use!"
#endif
	;

sge::plugin::manager::manager()
{
	SGE_LOG_DEBUG(
		log::global(),
		log::_1
			<< SGE_TEXT("Scanning for plugins in ")
			<< config::plugin_path()
	);

	filesystem::directory_iterator const end;
	for(
		filesystem::directory_iterator it(config::plugin_path());
		it != end;
		++it
	)
	{
		if(filesystem::is_directory(*it) || filesystem::extension(*it) != plugin_extension)
		{
			SGE_LOG_WARNING(
				log::global(),
				log::_1
					<< it->path().string()
					<< SGE_TEXT(" does not have the extension ")
					<< plugin_extension
					<< SGE_TEXT(" and thus is ignored!")
			);
			continue;
		}

		try
		{
			plugins.push_back(context_base(*it));
		}
		catch(library::function_not_found const &e)
		{
			SGE_LOG_WARNING(
				log::global(),
				log::_1
					<< it->path().string()
					<< SGE_TEXT(" doesn't seem to be a valid sge plugin")
					<< SGE_TEXT(" because the function \"")
					<< iconv(e.func())
					<< SGE_TEXT("\" is missing!")
			);
		}
		catch(exception const &e)
		{
			SGE_LOG_WARNING(
				log::global(),
				log::_1
					<< it->path().string()
					<< SGE_TEXT(" failed to load: \"")
					<< e.what()
					<< SGE_TEXT("\"!")
			);
		}
	}

	for(plugin_array::iterator it = plugins.begin(); it != plugins.end(); ++it)
		for(unsigned i = 1; i < capabilities::last_guard_; i <<= 1)
		{
			unsigned const type = it->type();
			if(type & i)
				categories[static_cast<capabilities::type>(i)].push_back(&*it);
		}
}

sge::plugin::manager::~manager()
{}
