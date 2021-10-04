//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_SCREEN_RESOURCES_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_SCREEN_RESOURCES_HPP_INCLUDED

#include <sge/opengl/xrandr/screen_resources_fwd.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


namespace sge::opengl::xrandr
{

class screen_resources
{
	FCPPT_NONMOVABLE(
		screen_resources
	);
public:
	explicit
	screen_resources(
		awl::backends::x11::window::const_base_ref
	);

	~screen_resources();

	[[nodiscard]]
	XRRScreenResources *
	get() const;

	[[nodiscard]]
	XRRScreenResources const &
	get_ref() const;
private:
	XRRScreenResources *const resources_;
};

}

#endif
