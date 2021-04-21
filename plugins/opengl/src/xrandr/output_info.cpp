//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/const_screen_resources_ref.hpp>
#include <sge/opengl/xrandr/output_info.hpp>
#include <sge/opengl/xrandr/screen_resources.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/screen_unit.hpp>
#include <sge/renderer/display_mode/dimensions.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::output_info::output_info(
	awl::backends::x11::display_ref const _display,
	sge::opengl::xrandr::const_screen_resources_ref const _resources,
	RROutput const _output
)
:
	info_(
		::XRRGetOutputInfo(
			_display.get().get(),
			_resources.get().get(),
			_output
		)
	)
{
	if(
		info_
		==
		nullptr
	)
	{
		throw
			sge::renderer::exception{
				FCPPT_TEXT("XRRGetOutputInfo")
			};
	}
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
