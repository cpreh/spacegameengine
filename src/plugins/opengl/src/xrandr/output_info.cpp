/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/xrandr/output_info.hpp>
#include <sge/opengl/xrandr/screen_resources.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/display_mode/dimensions.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::output_info::output_info(
	awl::backends::x11::display &_display,
	sge::opengl::xrandr::screen_resources const &_resources,
	RROutput const _output
)
:
	info_(
		::XRRGetOutputInfo(
			_display.get(),
			_resources.get(),
			_output
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

sge::opengl::xrandr::output_info::~output_info()
{
	::XRRFreeOutputInfo(
		info_
	);
}

sge::renderer::display_mode::dimensions
sge::opengl::xrandr::output_info::dimensions() const
{
	return
		sge::renderer::display_mode::dimensions(
			sge::renderer::screen_size(
				fcppt::cast::size<
					sge::renderer::screen_unit
				>(
					info_->mm_width
				),
				fcppt::cast::size<
					sge::renderer::screen_unit
				>(
					info_->mm_height
				)
			)
		);
}
