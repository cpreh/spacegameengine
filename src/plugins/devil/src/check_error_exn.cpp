/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/devil/check_error.hpp>
#include <sge/devil/check_error_exn.hpp>
#include <sge/devil/error_string.hpp>
#include <sge/image/exception.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>


void
sge::devil::check_error_exn()
{
	devil::optional_error const error(
		devil::check_error()
	);

	if(
		error
	)
		throw sge::image::exception(
			FCPPT_TEXT("The following devil error occured: ")
			+ devil::error_string(
				*error
			)
		);
}
