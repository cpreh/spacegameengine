//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/**
	Example description:

	Environment:
	Shows a black background with an fps counter at the top right and an
	instructional text at the top right of the screen. Uses a viewport
	that adapts to the window size.

	Purpose:
	Initially, a line is created from the current cursor position to the
	current cursor position. On a cursor move event, the last line's end
	point is updated to the current cursor position. On a button click,
	a new line is appended to the last line. The color changes smoothly
	from blue to red.

	This example shows the usage of:

	- sge::line_drawer::object in general (2D only)
	- font loading and display
	- viewport::fill_on_resize
	- fps counter
	- font::text::draw
	- Usage of sge::input::cursor
 */

#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/string.hpp>
#include <sge/font/system.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/draw/simple.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/event/button.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <sge/line_drawer/line.hpp>
#include <sge/line_drawer/object.hpp>
#include <sge/line_drawer/render_to_screen.hpp>
#include <sge/line_drawer/scoped_lock.hpp>
#include <sge/renderer/aspect.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vector2.hpp>
#include <sge/renderer/vector3.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/optional_object.hpp>
#include <sge/renderer/display_mode/parameters.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/target/base.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/renderer/target/viewport_size.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_font.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/timer/frames_counter.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manager.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/title.hpp>
#include <awl/show_error.hpp>
#include <awl/show_error_narrow.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_failure.hpp>
#include <awl/main/function_context.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/container/maybe_back.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/push_back.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>

namespace
{

// The line drawer currently only accepts three-dimensional points for
// its lines since it can be used to draw lines in "world space",
// too. In this example, we're just going to show the two-dimensional
// capabilities, so here's a function converting a 2D cursor position
// to a 3D position by just appending a 0 at the end.
sge::renderer::vector3 cursor_position_to_vector3(sge::input::cursor::position const &_pos)
{
  return fcppt::math::vector::push_back(
      fcppt::math::vector::structure_cast<sge::renderer::vector2, fcppt::cast::int_to_float_fun>(
          _pos),
      fcppt::literal<sge::renderer::scalar>(0));
}

}

awl::main::exit_code example_main(awl::main::function_context const &)
try
{
  sge::systems::instance<
      sge::systems::with_font,
      sge::systems::with_window,
      sge::systems::with_renderer<sge::systems::renderer_caps::ffp>,
      sge::systems::with_input> const
      sys(sge::systems::make_list(
          sge::systems::window(sge::systems::window_source(sge::systems::original_window(
              sge::window::title(FCPPT_TEXT("sge line drawer example"))))))(
          sge::systems::renderer(
              sge::renderer::pixel_format::object(
                  sge::renderer::pixel_format::color::depth32,
                  sge::renderer::pixel_format::depth_stencil::off,
                  sge::renderer::pixel_format::optional_multi_samples(),
                  sge::renderer::pixel_format::srgb::no),
              sge::renderer::display_mode::parameters(
                  sge::renderer::display_mode::vsync::on,
                  sge::renderer::display_mode::optional_object()),
              sge::viewport::optional_resize_callback{sge::viewport::fill_on_resize()}))(
          sge::systems::input(sge::systems::cursor_option_field::null())));

  sge::font::object_unique_ptr const font(
      sys.font_system().create_font(sge::font::parameters().family(FCPPT_TEXT("sans"))));

  sge::timer::frames_counter frames_counter;

  sge::line_drawer::object line_drawer{fcppt::make_ref(sys.renderer_device_core())};

  auto const move_event(
      [&line_drawer](sge::input::cursor::event::move const &_event)
      {
        fcppt::optional::maybe_void(
            _event.position(),
            [&line_drawer](sge::input::cursor::position const &_pos)
            {
              // To change the line drawer's geometry, we have to create a lock.
              sge::line_drawer::scoped_lock const lock{fcppt::make_ref(line_drawer)};

              fcppt::optional::maybe_void(
                  fcppt::container::maybe_back(lock.value()),
                  [_pos](fcppt::reference<sge::line_drawer::line> const _last)
                  {
                    // Then we can freely (!) change everything. When unlock is called
                    // (in the lock's destructor), all the geometry will be updated at
                    // once.
                    _last.get() = sge::line_drawer::line{
                        _last.get().begin(),
                        cursor_position_to_vector3(_pos),
                        sge::image::color::any::object(_last.get().begin_color()),
                        sge::image::color::any::object(_last.get().end_color())};
                  });
            });
      });

  auto const button_event(
      [&line_drawer](sge::input::cursor::event::button const &_event)
      {
        if (!_event.pressed())
        {
          return;
        }

        sge::line_drawer::scoped_lock const lock{fcppt::make_ref(line_drawer)};

        fcppt::optional::maybe(
            fcppt::container::maybe_back(lock.value()),
            [&_event, &lock]
            {
              sge::renderer::vector3 const pos3(cursor_position_to_vector3(_event.position()));

              lock.value().push_back(sge::line_drawer::line(
                  pos3,
                  pos3,
                  sge::image::color::any::object{sge::image::color::predef::red()},
                  sge::image::color::any::object{sge::image::color::predef::blue()}));
            },
            [&lock](fcppt::reference<sge::line_drawer::line> const _last)
            {
              lock.value().push_back(sge::line_drawer::line(
                  _last.get().end(),
                  _last.get().end(),
                  sge::image::color::any::object(_last.get().end_color()),
                  sge::image::color::any::object(_last.get().begin_color())));
            });
      });

  auto const draw(
      [&font, &frames_counter, &line_drawer, &sys]
      {
        frames_counter.update();

        sge::renderer::context::scoped_ffp const scoped_block(
            fcppt::make_ref(sys.renderer_device_ffp()),
            fcppt::reference_to_base<sge::renderer::target::base>(
                fcppt::make_ref(sys.renderer_device_ffp().onscreen_target())));

        scoped_block.get().clear(sge::renderer::clear::parameters().back_buffer(
            sge::image::color::any::object{sge::image::color::predef::black()}));

        // This function sets up an orthographic projection and calls
        // render. It's just a wrapper.
        sge::line_drawer::render_to_screen(
            sys.renderer_device_ffp(), scoped_block.get(), line_drawer);

        sge::font::vector const font_pos(fcppt::math::vector::null<sge::font::vector>());

        sge::font::align_h::max_width const font_width(
            fcppt::cast::size<sge::font::unit>(fcppt::cast::to_signed(
                sge::renderer::target::viewport_size(sys.renderer_device_ffp().onscreen_target())
                    .w())));

        sge::font::draw::simple(
            sys.renderer_device_ffp(),
            scoped_block.get(),
            *font,
            SGE_FONT_LIT("Press the left mouse button to set a point"),
            sge::font::text_parameters(
                sge::font::align_h::variant(sge::font::align_h::left(font_width))),
            font_pos,
            sge::image::color::any::object{sge::image::color::predef::red()},
            sge::renderer::texture::emulate_srgb::yes);

        sge::font::draw::simple(
            sys.renderer_device_ffp(),
            scoped_block.get(),
            *font,
            sge::font::from_fcppt_string(frames_counter.frames_str()) + SGE_FONT_LIT(" fps"),
            sge::font::text_parameters(
                sge::font::align_h::variant(sge::font::align_h::right(font_width))),
            font_pos,
            sge::image::color::any::object{sge::image::color::predef::red()},
            sge::renderer::texture::emulate_srgb::yes);
      });

  return sge::window::loop(
      sys.window_system(),
      sge::window::loop_function{
          [&sys, &button_event, &draw, &move_event](awl::event::base const &_event)
          {
            sge::systems::quit_on_escape(sys, _event);

            fcppt::optional::maybe_void(
                fcppt::variant::dynamic_cast_<
                    fcppt::mpl::list::object<
                        sge::renderer::event::render const,
                        sge::input::cursor::event::button const,
                        sge::input::cursor::event::move const>,
                    fcppt::cast::dynamic_fun>(_event),
                [&button_event, &draw, &move_event](auto const &_variant)
                {
                  fcppt::variant::match(
                      _variant,
                      [&draw](fcppt::reference<sge::renderer::event::render const>) { draw(); },
                      [&button_event](
                          fcppt::reference<sge::input::cursor::event::button const> const
                              _button_event) { button_event(_button_event.get()); },
                      [&move_event](
                          fcppt::reference<sge::input::cursor::event::move const> const _move_event)
                      { move_event(_move_event.get()); });
                });
          }});
}
catch (fcppt::exception const &_error)
{
  awl::show_error(_error.string());

  return awl::main::exit_failure();
}
catch (std::exception const &_error)
{
  awl::show_error_narrow(_error.what());

  return awl::main::exit_failure();
}
