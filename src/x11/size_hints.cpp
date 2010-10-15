/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/x11/size_hints.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

sge::x11::size_hints::size_hints(
	int const _min_w,
	int const _min_h,
	int const _desired_w,
	int const _desired_h
)
:
	hints_(
		XAllocSizeHints()
	)
{
	if(
		!hints_
	)
		throw sge::exception(
			FCPPT_TEXT("XAllocSizeHints() failed!")
		);

	hints_->flags = PSize | PMinSize;
	hints_->min_width = _min_w;
	hints_->min_height = _min_h;
	hints_->base_width = _desired_w;
	hints_->base_height = _desired_h;
}

XSizeHints *
sge::x11::size_hints::get() const
{
	return hints_;
}

sge::x11::size_hints::~size_hints()
{
	XFree(
		hints_
	);
}
