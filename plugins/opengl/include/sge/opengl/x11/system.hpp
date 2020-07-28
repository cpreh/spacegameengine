//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_X11_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_X11_SYSTEM_HPP_INCLUDED

#include <sge/opengl/platform/device_state_unique_ptr.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/opengl/x11/fullscreen_atom.hpp>
#include <sge/opengl/x11/state_atom.hpp>
#include <sge/opengl/xrandr/optional_system_unique_ptr.hpp>
#include <sge/renderer/display_mode/optional_fullscreen_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/x11/system/object_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>


namespace sge
{
namespace opengl
{
namespace x11
{

class system
:
	public sge::opengl::platform::system
{
	FCPPT_NONMOVABLE(
		system
	);
public:
	system(
		fcppt::log::object_reference,
		awl::backends::x11::system::object_ref
	);

	~system()
	override;
private:
	sge::opengl::platform::device_state_unique_ptr
	create_device_state(
		sge::renderer::display_mode::optional_fullscreen const &,
		sge::window::object_ref
	)
	override;

	fcppt::log::object_reference const log_;

	sge::opengl::xrandr::optional_system_unique_ptr const xrandr_system_;

	sge::opengl::x11::state_atom const wm_state_;

	sge::opengl::x11::fullscreen_atom const wm_fullscreen_;
};

}
}
}

#endif
