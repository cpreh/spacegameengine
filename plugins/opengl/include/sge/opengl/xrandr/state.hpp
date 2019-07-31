//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_STATE_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_STATE_HPP_INCLUDED

#include <sge/opengl/xrandr/configuration.hpp>
#include <sge/opengl/xrandr/extension.hpp>
#include <sge/opengl/xrandr/resolution_unique_ptr.hpp>
#include <sge/opengl/xrandr/state_fwd.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

class state
{
	FCPPT_NONCOPYABLE(
		state
	);
public:
	state(
		sge::opengl::xrandr::extension const &,
		sge::window::object &
	);

	~state();

	sge::renderer::display_mode::optional_object
	display_mode() const;

	sge::opengl::xrandr::resolution_unique_ptr
	choose_resolution(
		sge::renderer::display_mode::object const &
	);

	sge::renderer::display_mode::container
	display_modes() const;
private:
	awl::event::container
	on_event(
		awl::window::event::base const &
	);

	void
	update();

	sge::opengl::xrandr::extension const extension_;

	awl::backends::x11::window::base &window_;

	sge::opengl::xrandr::configuration const config_;

	sge::renderer::display_mode::optional_object display_mode_;

	sge::renderer::display_mode::container display_modes_;

	fcppt::signal::auto_connection const event_connection_;
};

}
}
}

#endif
