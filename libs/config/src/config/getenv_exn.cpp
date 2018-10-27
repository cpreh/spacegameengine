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


#include <sge/config/exception.hpp>
#include <sge/config/getenv.hpp>
#include <sge/config/getenv_exn.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>


// TODO: Remove this

fcppt::string
sge::config::getenv_exn(
	fcppt::string const &_name
)
{
	return
		fcppt::optional::to_exception(
			sge::config::getenv(
				_name
			),
			[
				&_name
			]{
				return
					sge::config::exception(
						FCPPT_TEXT("Missing env var: ")
						+
						_name
					);
			}
		);
}
