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


#include <sge/config/app_name.hpp>
#include <sge/config/cache_path.hpp>
#include <sge/config/company_name.hpp>
#include <sge/config/log_path.hpp>
#include <sge/src/config/try_create_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


boost::filesystem::path
sge::config::log_path(
	sge::config::company_name const &_company_name,
	sge::config::app_name const &_app_name
)
{
	boost::filesystem::path const path(
		sge::config::cache_path(
			sge::config::app_name(
				_company_name.get()
			)
		)
	);

	sge::config::try_create_path(
		path
	);

	return
		path
		/
		(
			_app_name.get()
			+
			FCPPT_TEXT(".txt")
		);
}
