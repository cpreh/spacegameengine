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


#include <sge/parse/impl/output/to_file.hpp>
#include <sge/parse/json/start_fwd.hpp>
#include <sge/parse/json/output/to_file.hpp>
#include <sge/parse/json/output/to_stream.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


bool
sge::parse::json::output::to_file(
	boost::filesystem::path const &_path,
	sge::parse::json::start const &_data
)
{
	return
		sge::parse::impl::output::to_file<
			char
		>(
			&sge::parse::json::output::to_stream,
			_path,
			_data
		);
}
