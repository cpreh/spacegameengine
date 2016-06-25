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


#include <sge/input/key/code.hpp>
#include <sge/x11input/key/code_from_event.hpp>
#include <sge/x11input/key/code_to_sym.hpp>
#include <sge/x11input/key/event_to_sge_code.hpp>
#include <sge/x11input/key/translate_code.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


sge::input::key::code
sge::x11input::key::event_to_sge_code(
	awl::backends::x11::display const &_display,
	XIDeviceEvent const &_event
)
{
	return
		sge::x11input::key::translate_code(
			sge::x11input::key::code_to_sym(
				_display,
				sge::x11input::key::code_from_event(
					_event
				)
			)
		);
}
