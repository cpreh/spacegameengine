/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "convert_class.hpp"
#include <sge/xcb/invalid_enum.hpp>
#include <sge/xcb/text.hpp>
#include <xcb/xcb.h>

boost::uint16_t
sge::xcb::window::convert_class(
	class_::type const value_
)
{
	switch(
		value_
	)
	{
	case class_::input_output:
		return XCB_WINDOW_CLASS_INPUT_OUTPUT;
	case class_::input_only:
		return XCB_WINDOW_CLASS_INPUT_ONLY;
	case class_::copy_from_parent:
		return XCB_WINDOW_CLASS_COPY_FROM_PARENT;
	}

	throw invalid_enum(
		SGE_XCB_TEXT("class_")
	);
}
