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


#include <sge/x11input/xim/context_fwd.hpp>
#include <sge/x11input/xim/get_filter_events.hpp>
#include <sge/x11input/xim/get_ic_values.hpp>
#include <awl/backends/x11/window/event/mask.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>


awl::backends::x11::window::event::mask
sge::x11input::xim::get_filter_events(
	sge::x11input::xim::context const &_context
)
{
	long mask{
		0l
	};

	sge::x11input::xim::get_ic_values(
		_context,
		XNFilterEvents,
		&mask
	);

	return
		awl::backends::x11::window::event::mask{
			mask
		};
}
