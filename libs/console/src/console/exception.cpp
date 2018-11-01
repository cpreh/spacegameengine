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


#include <sge/console/exception.hpp>
#include <sge/core/exception.hpp>
#include <sge/font/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::console::exception::exception(
	sge::font::string &&_console_string
)
:
	sge::core::exception(
		FCPPT_TEXT("console error")
	),
	console_string_(
		std::move(
			_console_string
		)
	)
{
}

sge::console::exception::exception(
	exception &&
)
= default;

sge::console::exception::exception(
	exception const &
)
= default;

sge::console::exception &
sge::console::exception::operator=(
	exception &&
)
= default;

sge::console::exception &
sge::console::exception::operator=(
	exception const &
)
= default;

sge::console::exception::~exception() noexcept
{
}

sge::font::string const &
sge::console::exception::console_string() const
{
	return
		console_string_;
}
