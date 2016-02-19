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


#include <sge/libpng/header_bytes.hpp>
#include <sge/libpng/is_png.hpp>
#include <sge/libpng/png.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <iosfwd>
#include <istream>
#include <fcppt/config/external_end.hpp>


bool
sge::libpng::is_png(
	std::istream &_stream
)
{
	std::array<
		char,
		sge::libpng::header_bytes::value
	>
	buf;

	std::streamsize const signed_size(
		fcppt::cast::to_signed(
			buf.size()
		)
	);

	_stream.read(
		buf.data(),
		signed_size
	);

	return
		_stream.gcount()
		>=
		signed_size
		&&
		::png_sig_cmp(
			fcppt::cast::to_char_ptr<
				png_byte *
			>(
				buf.data()
			),
			fcppt::literal<
				png_size_t
			>(
				0
			),
			fcppt::cast::size<
				png_size_t
			>(
				buf.size()
			)
		)
		==
		0;
}
