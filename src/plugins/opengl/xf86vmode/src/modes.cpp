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


#include "../modes.hpp"
#include "../check_extension.hpp"
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::xf86vmode::modes::modes(
	awl::backends::x11::display &_display,
	awl::backends::x11::screen const _screen
)
:
	display_(_display),
	screen_(_screen)
{
	xf86vmode::check_extension(
		display_
	);

	int mode_count;

	XF86VidModeModeInfo **ret;

	if(
		::XF86VidModeGetAllModeLines(
			display_.get(),
			this->screen().get(),
			&mode_count,
			&ret
		)
		== False
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("XF86VidModeGetAllModeLines() failed")
		);

	modes_.reset(
		ret
	);

	size_ =
		static_cast<
			size_type
		>(
			mode_count >= 0
			?
				mode_count
			:
				0
		);
}

sge::opengl::xf86vmode::modes::~modes()
{
}

XF86VidModeModeInfo const &
sge::opengl::xf86vmode::modes::operator[](
	size_type const _index
) const
{
	return (*modes_)[_index];
}

sge::opengl::xf86vmode::modes::size_type
sge::opengl::xf86vmode::modes::size() const
{
	return size_;
}

awl::backends::x11::display &
sge::opengl::xf86vmode::modes::display() const
{
	return display_;
}

awl::backends::x11::screen const
sge::opengl::xf86vmode::modes::screen() const
{
	return screen_;
}
