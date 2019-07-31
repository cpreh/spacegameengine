//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_WAYLAND_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_WAYLAND_SYSTEM_HPP_INCLUDED

#include <sge/opengl/platform/device_state_unique_ptr.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/renderer/display_mode/optional_fullscreen_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/wayland/system/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace wayland
{

class system
:
	public sge::opengl::platform::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	explicit
	system(
		awl::backends::wayland::system::object &
	);

	~system()
	override;
private:
	sge::opengl::platform::device_state_unique_ptr
	create_device_state(
		sge::renderer::display_mode::optional_fullscreen const &,
		sge::window::object &
	)
	override;
};

}
}
}

#endif
