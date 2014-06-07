/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/exception.hpp>
#include <sge/image/color/any/from_string.hpp>
#include <sge/image/color/any/print.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <ostream>
#include <fcppt/config/external_end.hpp>


int
main(
	int const argc,
	char *argv[])
try
{
	if(argc != 2)
	{
		fcppt::io::cout() << FCPPT_TEXT("Usage: ") << argv[0] << FCPPT_TEXT(" <color-string>\n");
		return EXIT_FAILURE;
	}
	fcppt::io::cout() << sge::image::color::any::from_string(argv[1]) << FCPPT_TEXT("\n");
	return EXIT_SUCCESS;
}
catch(
	 sge::image::exception const &e)
{
	 fcppt::io::cout() << e.string() << FCPPT_TEXT("\n");
	 return EXIT_FAILURE;
}
