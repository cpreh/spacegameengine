//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/xrandr/extension_fwd.hpp>
#include <sge/opengl/xrandr/get_version.hpp>
#include <sge/opengl/xrandr/version.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::xrandr::version
sge::opengl::xrandr::get_version(
	sge::opengl::xrandr::extension const &,
	awl::backends::x11::display &_display
)
{
	int major, minor;

	if(
		::XRRQueryVersion(
			_display.get(),
			&major,
			&minor
		)
		!=
		1
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Querying the xrandr version failed!")
		);

	return
		sge::opengl::xrandr::version(
			major,
			minor
		);
}
