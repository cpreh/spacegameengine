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
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>
#include <algorithm>

sge::config::optional_path const
sge::config::find_path(
	config::path_vector const &_config_files,
	fcppt::string const &_what,
	config::path_vector const &_hard_paths
)
{
	BOOST_FOREACH(
		path_vector::const_reference ref,
		_config_files
	)
	{
		parse::ini::section_vector result;

		if(
			!parse::ini::parse_file(
				ref,
				result
			)
		)
		{
			FCPPT_LOG_ERROR(
				sge::log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("Failed to parse ini file ")
					<< fcppt::filesystem::path_to_string(
						ref
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
						ref
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
						ref
					)
			);

			continue;
		}

		fcppt::filesystem::path const ret_path(
			entry_it->value
		);

		if(
			fcppt::filesystem::exists(
				ret_path
			)
		)
			return ret_path;
		else
		{
			FCPPT_LOG_ERROR(
				sge::log::global(),
				fcppt::log::_
					<< fcppt::filesystem::path_to_string(
						ret_path
					)
					<< FCPPT_TEXT(" does not exist!")
			);
		}
	}

	BOOST_FOREACH(
		path_vector::const_reference path,
		_hard_paths
	)
		if(
			fcppt::filesystem::exists(
				path
			)
		)
			return path;

	return optional_path();
}
