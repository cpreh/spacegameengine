//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_CRTC_INFO_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_CRTC_INFO_HPP_INCLUDED

#include <sge/opengl/xrandr/screen_resources_fwd.hpp>
#include <sge/renderer/display_mode/pixel_size_fwd.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/window/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class crtc_info
{
	FCPPT_NONCOPYABLE(
		crtc_info
	);
public:
	crtc_info(
		awl::backends::x11::display &,
		sge::opengl::xrandr::screen_resources const &,
		RRCrtc
	);

	~crtc_info();

	awl::backends::x11::window::rect
	rect() const;

	sge::renderer::display_mode::pixel_size
	pixel_size() const;

	RRMode
	mode() const;
private:
	XRRCrtcInfo *const info_;
};

}
}
}


#endif
