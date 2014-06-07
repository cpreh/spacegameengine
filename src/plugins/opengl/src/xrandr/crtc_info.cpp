/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/xrandr/crtc_info.hpp>
#include <sge/opengl/xrandr/screen_resources.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/window/rect.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::crtc_info::crtc_info(
	awl::backends::x11::display &_display,
	sge::opengl::xrandr::screen_resources const &_screen_resources,
	RRCrtc const _crtc
)
:
	info_(
		::XRRGetCrtcInfo(
			_display.get(),
			_screen_resources.get(),
			_crtc
		)
	)
{
	FCPPT_ASSERT_THROW(
		info_
		!=
		nullptr,
		sge::renderer::exception
	);
}

sge::opengl::xrandr::crtc_info::~crtc_info()
{
	::XRRFreeCrtcInfo(
		info_
	);
}

awl::window::rect const
sge::opengl::xrandr::crtc_info::rect() const
{
	return
		awl::window::rect(
			awl::window::rect::vector(
				info_->x,
				info_->y
			),
			awl::window::rect::dim(
				fcppt::cast::to_signed(
					info_->width
				),
				fcppt::cast::to_signed(
					info_->height
				)
			)
		);
}

sge::renderer::display_mode::pixel_size const
sge::opengl::xrandr::crtc_info::pixel_size() const
{
	return
		sge::renderer::display_mode::pixel_size(
			sge::renderer::screen_size(
				info_->width,
				info_->height
			)
		);
}

RRMode
sge::opengl::xrandr::crtc_info::mode() const
{
	return
		info_->mode;
}
