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


#include <sge/x11input/xim/lc_ctype.hpp>
#include <fcppt/getenv.hpp>
#include <fcppt/optional_std_string.hpp>
#include <fcppt/optional/alternative.hpp>


fcppt::optional_std_string
sge::x11input::xim::lc_ctype()
{
	return
		fcppt::optional::alternative(
			fcppt::optional::alternative(
				fcppt::getenv(
					"LC_ALL"
				),
				fcppt::getenv(
					"LC_CTYPE"
				)
			),
			fcppt::getenv(
				"LANG"
			)
		);
}
