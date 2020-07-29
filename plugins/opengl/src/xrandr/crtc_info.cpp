//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/const_screen_resources_ref.hpp>
#include <sge/opengl/xrandr/crtc_info.hpp>
#include <sge/opengl/xrandr/screen_resources.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/display_mode/pixel_size.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/display_ref.hpp>
#include <awl/backends/x11/window/rect.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::crtc_info::crtc_info(
	awl::backends::x11::display_ref const _display,
	sge::opengl::xrandr::const_screen_resources_ref const _screen_resources,
	RRCrtc const _crtc
)
:
	info_(
		::XRRGetCrtcInfo(
			_display.get().get(),
			_screen_resources.get().get(),
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

awl::backends::x11::window::rect
sge::opengl::xrandr::crtc_info::rect() const
{
	return
		awl::backends::x11::window::rect{
			awl::backends::x11::window::rect::vector{
				info_->x,
				info_->y
			},
			awl::backends::x11::window::rect::dim{
				fcppt::cast::to_signed(
					info_->width
				),
				fcppt::cast::to_signed(
					info_->height
				)
			}
		};
}

sge::renderer::display_mode::pixel_size
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
