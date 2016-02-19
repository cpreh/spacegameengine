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


#include <sge/font/added.hpp>
#include <sge/font/exception.hpp>
#include <sge/pango/added.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fontconfig/fontconfig.h>
#include <fcppt/config/external_end.hpp>


sge::pango::added::added(
	boost::filesystem::path const &_path
)
:
	sge::font::added()
{
	if(
		::FcConfigAppFontAddFile(
			nullptr,
			fcppt::cast::to_char_ptr<
				FcChar8 const *
			>(
				_path.string().c_str()
			)
		)
		!=
		FcTrue
	)
		throw
			sge::font::exception{
				FCPPT_TEXT("Unable to add font ")
				+
				fcppt::filesystem::path_to_string(
					_path
				)
			};
}

sge::pango::added::~added()
{
	// TODO: Can we free this custom font?
}
