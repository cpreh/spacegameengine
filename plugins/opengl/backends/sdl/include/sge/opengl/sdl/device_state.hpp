//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_SDL_DEVICE_STATE_HPP_INCLUDED
#define SGE_OPENGL_SDL_DEVICE_STATE_HPP_INCLUDED

#include <sge/opengl/platform/device_state.hpp>
#include <sge/renderer/display_mode/optional_fullscreen_fwd.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/sdl/window/object_ref.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::sdl
{

class device_state : public sge::opengl::platform::device_state
{
  FCPPT_NONMOVABLE(device_state);

public:
  device_state(sge::renderer::display_mode::optional_fullscreen const &, sge::window::object_ref);

  ~device_state() override;

  [[nodiscard]] sge::renderer::display_mode::optional_object display_mode() const override;

  void fullscreen(sge::renderer::display_mode::optional_fullscreen const &) override;

private:
  void do_fullscreen(sge::renderer::display_mode::optional_fullscreen const &);

  awl::backends::sdl::window::object_ref const window_;
};

}

#endif
