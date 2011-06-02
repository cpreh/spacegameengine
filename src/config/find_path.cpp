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


#include <sge/config/find_path.hpp>
#include <sge/log/global.hpp>
#include <sge/parse/ini/parse_file.hpp>
#include <sge/parse/ini/header_name_equal.hpp>
#include <sge/parse/ini/entry_name_equal.hpp>
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <fcppt/filesystem/exists.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <algorithm>

sge::config::optional_path const
sge::config::find_path(
	config::path_vector const &_config_files,
	fcppt::string const &_what,
	config::path_vector const &_hard_paths
)
{
	for(
		path_vector::const_iterator it(
			_config_files.begin()
		);
		it != _config_files.end();
		++it
	)
	{
		parse::ini::section_vector result;

		if(
			!fcppt::filesystem::exists(
				*it
			)
		)
		{
			FCPPT_LOG_DEBUG(
				sge::log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("Config file ")
					<< *it
					<< FCPPT_TEXT(" does not exist.")
			);

			continue;
		}

		if(
			!parse::ini::parse_file(
				*it,
				result
			)
		)
		{
			FCPPT_LOG_ERROR(
				sge::log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("Failed to parse ini file ")
					<< fcppt::filesystem::path_to_string(
						*it	
					)
			);

			continue;
		}

		parse::ini::section_vector::const_iterator const section_it(
			std::find_if(
				result.begin(),
				result.end(),
				parse::ini::header_name_equal(
					FCPPT_TEXT("paths")
				)
			)
		);

		if(
			section_it == result.end()
		)
		{
			FCPPT_LOG_ERROR(
				sge::log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("Cannot find section [paths] in ")
					<< fcppt::filesystem::path_to_string(
						*it	
					)
			);

			continue;
		}

		parse::ini::entry_vector const &entries(
			section_it->entries
		);

		sge::parse::ini::entry_vector::const_iterator const entry_it(
			std::find_if(
				entries.begin(),
				entries.end(),
				parse::ini::entry_name_equal(
					_what
				)
			)		
		);

		if(
			entry_it == entries.end()
		)
		{
			FCPPT_LOG_ERROR(
				sge::log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("Cannot find entry ")
					<< _what
					<< FCPPT_TEXT(" in section [paths] in ")
					<< fcppt::filesystem::path_to_string(
						*it	
					)
			);

			continue;
		}

		fcppt::filesystem::path const ret_path(
			entry_it->value
		);

		if(
			!fcppt::filesystem::exists(
				ret_path
			)
		)
		{
			FCPPT_LOG_ERROR(
				sge::log::global(),
				fcppt::log::_
					<< _what
					<< FCPPT_TEXT(" points to ")
					<< fcppt::filesystem::path_to_string(
						ret_path
					)
					<< FCPPT_TEXT(" which does not exist!")
			);

			continue;
		}
		
		return ret_path;
	}

	for(
		path_vector::const_iterator it(
			_hard_paths.begin()
		);
		it != _hard_paths.end();
		++it
	)
		if(
			fcppt::filesystem::exists(
				*it
			)
		)
			return *it;

	return optional_path();
}
