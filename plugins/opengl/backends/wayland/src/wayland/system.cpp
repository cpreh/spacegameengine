//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/platform/device_state_unique_ptr.hpp>
#include <sge/opengl/platform/system.hpp>
#include <sge/opengl/wayland/device_state.hpp>
#include <sge/opengl/wayland/system.hpp>
#include <sge/renderer/display_mode/optional_fullscreen.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/wayland/system/object_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>

sge::opengl::wayland::system::system(awl::backends::wayland::system::object_ref const /*_system*/
                                     )
    : sge::opengl::platform::system()
{
}

sge::opengl::wayland::system::~system() = default;

sge::opengl::platform::device_state_unique_ptr sge::opengl::wayland::system::create_device_state(
    sge::renderer::display_mode::optional_fullscreen const &_fullscreen,
    sge::window::object_ref const /*_window*/
)
{
  return fcppt::unique_ptr_to_base<sge::opengl::platform::device_state>(
      fcppt::make_unique_ptr<sge::opengl::wayland::device_state>(_fullscreen));
}
