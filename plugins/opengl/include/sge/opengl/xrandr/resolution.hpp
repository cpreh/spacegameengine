//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_RESOLUTION_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_RESOLUTION_HPP_INCLUDED

#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <sge/opengl/xrandr/mode.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/resolution_fwd.hpp>
#include <sge/renderer/display_mode/optional_refresh_rate_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class resolution
{
	FCPPT_NONCOPYABLE(
		resolution
	);
public:
	resolution(
		awl::backends::x11::window::base const &,
		sge::opengl::xrandr::configuration const &,
		sge::opengl::xrandr::mode_index,
		sge::renderer::display_mode::optional_refresh_rate const &,
		sge::opengl::xrandr::mode const &old_mode
	);

	~resolution();
private:
	awl::backends::x11::window::base const &window_;

	sge::opengl::xrandr::configuration const &config_;

	sge::opengl::xrandr::mode const old_mode_;
};

}
}
}

#endif
