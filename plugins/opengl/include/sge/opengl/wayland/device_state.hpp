//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_WAYLAND_DEVICE_STATE_HPP_INCLUDED
#define SGE_OPENGL_WAYLAND_DEVICE_STATE_HPP_INCLUDED

#include <sge/opengl/platform/device_state.hpp>
#include <sge/renderer/display_mode/optional_fullscreen_fwd.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::opengl::wayland
{

class device_state : public sge::opengl::platform::device_state
{
  FCPPT_NONMOVABLE(device_state);

public:
  explicit device_state(sge::renderer::display_mode::optional_fullscreen const &);

  ~device_state() override;

private:
  [[nodiscard]] sge::renderer::display_mode::optional_object display_mode() const override;

  void fullscreen(sge::renderer::display_mode::optional_fullscreen const &) override;

  void do_fullscreen(sge::renderer::display_mode::optional_fullscreen const &);
};

}

#endif
