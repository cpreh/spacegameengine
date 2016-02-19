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


#include <sge/image/exception.hpp>
#include <sge/libpng/create_struct.hpp>
#include <sge/libpng/error_context_fwd.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/read_ptr.hpp>
#include <fcppt/text.hpp>


sge::libpng::read_ptr::read_ptr(
	sge::libpng::error_context &_error_context
)
:
	ptr_(
		sge::libpng::create_struct(
			&::png_create_read_struct,
			_error_context
		)
	)
{
	if(
		ptr_
		==
		nullptr
	)
		throw
			sge::image::exception{
				FCPPT_TEXT("couldn't allocate png read structure")
			};
}

sge::libpng::read_ptr::~read_ptr()
{
	::png_destroy_read_struct(
		&ptr_,
		nullptr,
		nullptr
	);
}

png_structp
sge::libpng::read_ptr::ptr() const
{
	return
		ptr_;
}
