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


#include <sge/config/find_path.hpp>
#include <sge/config/path_not_found.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/filesystem/exists.hpp>
#include <sge/parse/ini/parse_file.hpp>
#include <sge/parse/ini/header_name_equal.hpp>
#include <sge/parse/ini/entry_name_equal.hpp>
#include <sge/parse/ini/entry.hpp>
#include <sge/parse/ini/section.hpp>
#include <sge/parse/ini/section_vector.hpp>
#include <sge/algorithm/find_if_exn.hpp>
#include <sge/log/headers.hpp>
#include <sge/log/global.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>

namespace
{

sge::filesystem::path const
try_path(
	sge::filesystem::path const &p)
{
	if(
		sge::filesystem::exists(
			p
		)
	)
		return p;

	throw sge::exception(
		p.string() + FCPPT_TEXT(" does not exist")
	);
}

}

sge::filesystem::path const
sge::config::find_path(
	path_vector const &config_files,
	string const &what,
	path_vector const &hard_paths)
{
	BOOST_FOREACH(
		path_vector::const_reference r,
		config_files
	)
	{
		try
		{
			parse::ini::section_vector result;

			parse::ini::parse_file(
				r,
				result
			);

			parse::ini::section const &section(
				*algorithm::find_if_exn(
					result.begin(),
					result.end(),
					parse::ini::header_name_equal(
						FCPPT_TEXT("paths")
					)
				)
			);

			parse::ini::entry_vector const &entries(
				section.entries
			);

			return try_path(
				algorithm::find_if_exn(
					entries.begin(),
					entries.end(),
					parse::ini::entry_name_equal(
						what
					)
				)->value
			);
		}
		catch(
			sge::exception const &e
		)
		{
			SGE_LOG_DEBUG(
				log::global(),
				log::_
					<< e.string()
			);
		}
	}

	BOOST_FOREACH(
		path_vector::const_reference r,
		hard_paths
	)
		try
		{
			return try_path(
				r
			);
		}
		catch(exception const &e)
		{
			SGE_LOG_DEBUG(
				log::global(),
				log::_
					<< e.string()
			);
		}

	throw path_not_found(
		what
	);
}
