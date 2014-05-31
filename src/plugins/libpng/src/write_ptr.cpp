/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/libpng/write_ptr.hpp>
#include <fcppt/text.hpp>


sge::libpng::write_ptr::write_ptr(
	sge::libpng::error_context &_error_context
)
:
	ptr_{
		sge::libpng::create_struct(
			&::png_create_write_struct,
			_error_context
		)
	}
{
	if(
		ptr_
		==
		nullptr
	)
		throw
			sge::image::exception{
				FCPPT_TEXT("couldn't allocate png write structure")
			};
}

sge::libpng::write_ptr::~write_ptr()
{
	::png_destroy_write_struct(
		&ptr_,
		nullptr
	);
}

png_structp
sge::libpng::write_ptr::ptr() const
{
	return
		ptr_;
}
