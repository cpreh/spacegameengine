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


#include <sge/media/const_raw_range.hpp>
#include <sge/media/impl/raw_streambuf.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <streambuf>
#include <fcppt/config/external_end.hpp>


sge::media::impl::raw_streambuf::raw_streambuf(
	sge::media::const_raw_range const &_range
)
:
	std::streambuf()
{
	auto const convert(
		[](
			sge::media::const_raw_pointer const _ptr
		)
		-> char_type *
		{
			// The streambuf should never write to
			// this unless pbackfail has
			// non-default behavior
			return
				const_cast<
					char_type *
				>(
					fcppt::cast::to_char_ptr<
						char_type const *
					>(
						_ptr
					)
				);
		}
	);

	char_type *const beg(
		convert(
			_range.begin()
		)
	);

	char_type *const end(
		convert(
			_range.end()
		)
	);

	this->setg(
		beg,
		beg,
		end
	);
}

sge::media::impl::raw_streambuf::~raw_streambuf()
{
}
