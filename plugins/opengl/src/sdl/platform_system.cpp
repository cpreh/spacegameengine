//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/platform/device_state_unique_ptr.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/opengl/sdl/device_state.hpp>
#include <sge/opengl/sdl/platform_system.hpp>
#include <sge/renderer/display_mode/optional_fullscreen_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/backends/sdl/system/object_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::opengl::sdl::platform_system::platform_system(
	awl::backends::sdl::system::object &
)
:
	sge::opengl::platform::system{}
{
}

sge::opengl::sdl::platform_system::~platform_system()
{
}

sge::opengl::platform::device_state_unique_ptr
sge::opengl::sdl::platform_system::create_device_state(
	sge::renderer::display_mode::optional_fullscreen const &_fullscreen,
	sge::window::object &_window
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::opengl::platform::device_state
		>(
			fcppt::make_unique_ptr<
				sge::opengl::sdl::device_state
			>(
				_fullscreen,
				_window
			)
		);
}
