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


#include "../dga.hpp"
#include <sge/x11/window.hpp>
#ifdef SGE_USE_DGA
#include "../check_dga_mouse.hpp"
#include <X11/extensions/Xxf86dga.h>
#include <sge/x11/display.hpp>
#include <sge/log/global.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/function_once.hpp>
#include <fcppt/text.hpp>
#endif

namespace
{

void
init_dga(
	sge::x11::window_ptr
);

bool have_dga = false;

}

sge::x11input::dga::dga(
	x11::window_ptr const wnd
)
:
	wnd(wnd),
	enabled(false)
{
	init_dga(wnd);
	enable(true);
}

sge::x11input::dga::~dga()
{
	enable(false);
}

void
sge::x11input::dga::enable(
	bool
#ifdef SGE_USE_DGA
	const b
#endif
)
{
#ifdef SGE_USE_DGA
	if(enabled == b)
		return;

	if(!have_dga)
		return;

	if(
		XF86DGADirectVideo(
			wnd->display()->get(),
			wnd->screen(),
			b
			? XF86DGADirectMouse
			: 0
		)
		!= True
	)
	{
		FCPPT_LOG_ERROR(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Failed to enable or disable dga mouse!")
		);

		return;
	}

	enabled = b;
#endif
}

bool
sge::x11input::dga::useable() const
{
	return have_dga;
}

namespace
{

void
init_dga(
	sge::x11::window_ptr
#ifdef SGE_USE_DGA
	const wnd
#endif
)
{
#ifdef SGE_USE_DGA
	FCPPT_FUNCTION_ONCE

	have_dga = sge::x11input::check_dga_mouse(
		wnd
	);

	if(have_dga)
		return;

	FCPPT_LOG_WARNING(
		sge::log::global(),
		fcppt::log::_
			<< FCPPT_TEXT(
				"You compiled spacegameengine with DGA support but DGA Mouse is not supported by your system!"
				"Maybe you are missing libXxf86dga or a proper video driver? Disabling dga."
			)
	);
#endif
}

}
