//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/xrandr/choose_resolution.hpp>
#include <sge/opengl/xrandr/current_display_mode.hpp>
#include <sge/opengl/xrandr/display_modes.hpp>
#include <sge/opengl/xrandr/extension.hpp>
#include <sge/opengl/xrandr/input_mask.hpp>
#include <sge/opengl/xrandr/resolution.hpp>
#include <sge/opengl/xrandr/resolution_unique_ptr.hpp>
#include <sge/opengl/xrandr/select_input.hpp>
#include <sge/opengl/xrandr/state.hpp>
#include <sge/opengl/xrandr/update_configuration.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/display_mode/container.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/x11/default_screen.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <awl/backends/x11/window/root.hpp>
#include <awl/backends/x11/window/event/generic.hpp>
#include <awl/backends/x11/window/event/type.hpp>
#include <awl/event/container.hpp>
#include <awl/window/object.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_const.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/randr.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::xrandr::state::state(
    sge::opengl::xrandr::extension const &_extension, sge::window::object_ref const _window)
    : extension_{_extension},
      window_{
          fcppt::optional::to_exception(
              fcppt::cast::dynamic<awl::backends::x11::window::base>(_window.get().awl_object()),
              []
              {
                return sge::renderer::exception{
                    FCPPT_TEXT("Window passed to xrandr::state is not an X11 window.")};
              })
              .get()},
      config_{fcppt::reference_to_const(window_)},
      display_mode_{},
      display_modes_{},
      event_connection_{_window.get().event_handler(sge::window::event_function{
          [this](awl::window::event::base const &_event) { return this->on_event(_event); }})}
{
  // TODO(philipp): Select configure notify?

  sge::opengl::xrandr::select_input(
      // TODO(philipp): root_window?
      *awl::backends::x11::window::root(
          window_.get().display(), awl::backends::x11::default_screen(window_.get().display())),
      fcppt::strong_typedef_construct_cast<
          sge::opengl::xrandr::input_mask,
          fcppt::cast::size_fun>(RRScreenChangeNotifyMask // NOLINT(hicpp-signed-bitwise)
                                 ));

  this->update();
}

sge::opengl::xrandr::state::~state() = default;

sge::renderer::display_mode::optional_object sge::opengl::xrandr::state::display_mode() const
{
  return display_mode_;
}

sge::opengl::xrandr::resolution_unique_ptr sge::opengl::xrandr::state::choose_resolution(
    sge::renderer::display_mode::object const &_display_mode)
{
  return sge::opengl::xrandr::choose_resolution(
      fcppt::make_cref(config_), fcppt::reference_to_const(window_), _display_mode);
}

sge::renderer::display_mode::container sge::opengl::xrandr::state::display_modes() const
{
  return display_modes_;
}

awl::event::container sge::opengl::xrandr::state::on_event(awl::window::event::base const &_event)
{
  fcppt::optional::maybe_void(
      fcppt::cast::dynamic<awl::backends::x11::window::event::generic const>(_event),
      [this](fcppt::reference<awl::backends::x11::window::event::generic const> const _x11_event)
      {
        awl::backends::x11::window::event::type const type{_x11_event.get().event().get().type};

        if (type ==
                awl::backends::x11::window::event::type{
                    this->extension_.event_base().get() + RRScreenChangeNotify} ||
            type == awl::backends::x11::window::event::type{ConfigureNotify})
        {
          if (sge::opengl::xrandr::update_configuration(_x11_event.get().event()))
          {
            this->update();
          }
        }
      });

  // TODO(philipp): Return events here?
  return awl::event::container{};
}

void sge::opengl::xrandr::state::update()
{
  display_mode_ = sge::opengl::xrandr::current_display_mode(window_.get());

  display_modes_ = sge::opengl::xrandr::display_modes(config_);
}
