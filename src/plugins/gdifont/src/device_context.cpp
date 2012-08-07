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


#include <sge/font/exception.hpp>
#include <sge/gdifont/device_context.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>


sge::gdifont::device_context::device_context()
:
	hdc_(
		::CreateCompatibleDC(
			fcppt::null_ptr()
		)
	)
{
	if(
		hdc_ == fcppt::null_ptr()
	)
		throw sge::font::exception(
			FCPPT_TEXT("CreateCompatibleDC failed!")
		);
}

sge::gdifont::device_context::~device_context()
{
	FCPPT_ASSERT_ERROR(
		::DeleteDC(
			hdc_
		)
		!= 0
	);
}

HDC
sge::gdifont::device_context::get() const
{
	return hdc_;
}
