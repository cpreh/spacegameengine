/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/libpng/png.hpp>
#include <sge/libpng/read_ptr.hpp>
#include <fcppt/text.hpp>


sge::libpng::read_ptr::read_ptr(
	png_const_charp const _user_png_ver,
	png_voidp const _error_ptr,
	png_error_ptr const _error_fn,
	png_error_ptr const _warn_fn
)
:
	ptr_(
		png_create_read_struct(
			_user_png_ver,
			_error_ptr,
			_error_fn,
			_warn_fn
		)
	)
{
	if(
		!ptr_
	)
		throw image::exception(
			FCPPT_TEXT("couldn't allocate png read structure")
		);
}

sge::libpng::read_ptr::~read_ptr()
{
	png_destroy_read_struct(
		&ptr_,
		0,
		0
	);
}

png_structp
sge::libpng::read_ptr::ptr() const
{
	return ptr_;
}
