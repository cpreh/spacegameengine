/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/plugin/manager.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/library/symbol_not_found.hpp>
#include <sge/log/global.hpp>
#include <sge/exception.hpp>
#include <fcppt/filesystem/directory_iterator.hpp>
#include <fcppt/filesystem/is_directory.hpp>
#include <fcppt/filesystem/extension_without_dot.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/foreach_enumerator.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config.hpp>
#include <boost/foreach.hpp>

namespace
{

fcppt::char_type const *const plugin_extension =
#ifdef FCPPT_DARWIN_PLATFORM
	FCPPT_TEXT("dylib")
#elif FCPPT_POSIX_PLATFORM
	FCPPT_TEXT("so")
#elif FCPPT_WINDOWS_PLATFORM
	FCPPT_TEXT("dll")
#else
#error "Don't know which plugin extension to use!"
#endif
	;

}

sge::plugin::manager::manager(
	fcppt::filesystem::path const &_path
)
:
	plugins_(),
	categories_()
{
	FCPPT_LOG_DEBUG(
		log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("Scanning for plugins in ")
			<< fcppt::filesystem::path_to_string(
				_path
			)
	);

	fcppt::filesystem::directory_iterator const it_end;

	for(
		fcppt::filesystem::directory_iterator it(
			_path
		);
		it != it_end;
		++it
	)
	{
		if(
			fcppt::filesystem::is_directory(*it)
			|| fcppt::filesystem::extension_without_dot(*it) != plugin_extension
		)
		{
			FCPPT_LOG_WARNING(
				log::global(),
				fcppt::log::_
					<< fcppt::filesystem::path_to_string(
						it->path()
					)
					<< FCPPT_TEXT(" does not have the extension ")
					<< plugin_extension
					<< FCPPT_TEXT(" and thus is ignored!")
			);
			continue;
		}

		try
		{
			plugins_.push_back(
				plugin::context_base(
					it->path()
				)
			);
		}
		catch(
			library::symbol_not_found const &_exception
		)
		{
			FCPPT_LOG_WARNING(
				log::global(),
				fcppt::log::_
					<< fcppt::filesystem::path_to_string(
						it->path()
					)
					<< FCPPT_TEXT(" doesn't seem to be a valid sge plugin")
					<< FCPPT_TEXT(" because the symbol \"")
					<< fcppt::from_std_string(
						_exception.symbol()
					)
					<< FCPPT_TEXT("\" is missing!")
			);
		}
		catch(
			sge::exception const &_exception
		)
		{
			FCPPT_LOG_WARNING(
				log::global(),
				fcppt::log::_
					<< fcppt::filesystem::path_to_string(
						it->path()
					)
					<< FCPPT_TEXT(" failed to load: \"")
					<< _exception.string()
					<< FCPPT_TEXT("\"!")
			);
		}
	}

	BOOST_FOREACH(
		plugin_array::reference ref,
		plugins_
	)
		FCPPT_FOREACH_ENUMERATOR(
			index,
			plugin::capabilities
		)
			if(
				ref.info().capabilities() & index
			)
				categories_[
					index
				].push_back(
					&ref
				);

}

sge::plugin::manager::~manager()
{
}
