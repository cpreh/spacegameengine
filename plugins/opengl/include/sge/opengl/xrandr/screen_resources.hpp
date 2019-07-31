//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_SCREEN_RESOURCES_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_SCREEN_RESOURCES_HPP_INCLUDED

#include <sge/opengl/xrandr/screen_resources_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
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

class screen_resources
{
	FCPPT_NONCOPYABLE(
		screen_resources
	);
public:
	explicit
	screen_resources(
		awl::backends::x11::window::base const &
	);

	~screen_resources();

	XRRScreenResources *
	get() const;

	XRRScreenResources const &
	get_ref() const;
private:
	XRRScreenResources *const resources_;
};

}
}
}

#endif
