//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_X11_DEVICE_STATE_HPP_INCLUDED
#define SGE_OPENGL_X11_DEVICE_STATE_HPP_INCLUDED

#include <sge/opengl/platform/device_state.hpp>
#include <sge/opengl/x11/fullscreen_atom.hpp>
#include <sge/opengl/x11/state_atom.hpp>
#include <sge/opengl/xrandr/optional_system_ref_fwd.hpp>
#include <sge/opengl/xrandr/resolution_fwd.hpp>
#include <sge/opengl/xrandr/state_fwd.hpp>
#include <sge/renderer/display_mode/optional_fullscreen_fwd.hpp>
#include <sge/renderer/display_mode/optional_object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/x11/window/base_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/object_decl.hpp>

namespace sge::opengl::x11
{

class device_state : public sge::opengl::platform::device_state
{
  FCPPT_NONMOVABLE(device_state);

public:
  device_state(
      fcppt::log::object_reference,
      sge::opengl::xrandr::optional_system_ref const &,
      sge::renderer::display_mode::optional_fullscreen const &,
      sge::window::object_ref,
      sge::opengl::x11::state_atom,
      sge::opengl::x11::fullscreen_atom);

  ~device_state() override;

private:
  [[nodiscard]] sge::renderer::display_mode::optional_object display_mode() const override;

  void fullscreen(sge::renderer::display_mode::optional_fullscreen const &) override;

  void do_fullscreen(sge::renderer::display_mode::optional_fullscreen const &);

  using xrandr_state_unique_ptr = fcppt::unique_ptr<sge::opengl::xrandr::state>;

  using optional_xrandr_state_unique_ptr = fcppt::optional::object<xrandr_state_unique_ptr>;

  using resolution_unique_ptr = fcppt::unique_ptr<sge::opengl::xrandr::resolution>;

  using optional_resolution_unique_ptr = fcppt::optional::object<resolution_unique_ptr>;

  fcppt::log::object_reference const log_;

  optional_xrandr_state_unique_ptr const xrandr_state_;

  sge::opengl::x11::state_atom const wm_state_;

  sge::opengl::x11::fullscreen_atom const wm_fullscreen_;

  awl::backends::x11::window::base_ref const window_;

  optional_resolution_unique_ptr resolution_;
};

}

#endif
