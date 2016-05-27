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


#include <sge/input/exception.hpp>
#include <sge/wlinput/xkb_context.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xkbcommon/xkbcommon.h>
#include <fcppt/config/external_end.hpp>


sge::wlinput::xkb_context::xkb_context()
:
	context_{
		::xkb_context_new(
			XKB_CONTEXT_NO_FLAGS
		)
	}
{
	if(
		context_
		==
		nullptr
	)
		throw
			sge::input::exception{
				FCPPT_TEXT("xkb_context_new failed")
			};
}

sge::wlinput::xkb_context::~xkb_context()
{
	::xkb_context_unref(
		context_
	);
}

::xkb_context *
sge::wlinput::xkb_context::get() const
{
	return
		context_;
}
