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


#include <sge/parse/impl/file_error_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/parse/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::string
common_error(
	boost::filesystem::path const &_path
)
{
	return
		FCPPT_TEXT("Error in file ")
		+
		fcppt::filesystem::path_to_string(
			_path
		)
		+
		FCPPT_TEXT(" : ");
}

}

fcppt::string
sge::parse::impl::file_error_string(
	boost::filesystem::path const &_path,
	fcppt::parse::error<
		char
	> &&_error
)
{
	return
		common_error(
			_path
		)
		+
		fcppt::from_std_string(
			std::move(
				_error.get()
			)
		);
}

fcppt::string
sge::parse::impl::file_error_string(
	boost::filesystem::path const &_path,
	fcppt::parse::error<
		wchar_t
	> &&_error
)
{
	return
		fcppt::optional::maybe(
			fcppt::from_std_wstring(
				std::move(
					_error.get()
				)
			),
			[
				&_path
			]{
				return
					common_error(
						_path
					)
					+
					FCPPT_TEXT("Failed to convert error message!");
			},
			[
				&_path
			](
				fcppt::string &&_fcppt_error
			)
			{
				return
					common_error(
						_path
					)
					+
					std::move(
						_fcppt_error
					);
			}
		);
}
