//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_PLATFORM_SYSTEM_HPP_INCLUDED
#define SGE_OPENGL_PLATFORM_SYSTEM_HPP_INCLUDED

#include <sge/opengl/platform/device_state_unique_ptr.hpp>
#include <sge/opengl/platform/system_fwd.hpp>
#include <sge/renderer/display_mode/optional_fullscreen_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::platform
{

class system
{
  FCPPT_NONMOVABLE(system);

protected:
  system();

public:
  virtual ~system();

  [[nodiscard]] virtual sge::opengl::platform::device_state_unique_ptr create_device_state(
      sge::renderer::display_mode::optional_fullscreen const &, sge::window::object_ref) = 0;
};

}

#endif
