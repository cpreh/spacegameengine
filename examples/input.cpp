//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/console/muxing.hpp>
#include <sge/console/muxing_fcppt_streambuf.hpp>
#include <sge/console/object.hpp>
#include <sge/console/prefix.hpp>
#include <sge/console/gfx/font_color.hpp>
#include <sge/console/gfx/input_active.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/console/gfx/output_line_limit.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object.hpp>
#include <sge/font/object_unique_ptr.hpp>
#include <sge/font/parameters.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/system.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/input/log_location.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/button_code_to_string.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/scroll_code_to_string.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/button.hpp>
#include <sge/input/cursor/event/discover.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <sge/input/cursor/event/remove.hpp>
#include <sge/input/cursor/event/scroll.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/discover.hpp>
#include <sge/input/focus/event/in.hpp>
#include <sge/input/focus/event/key.hpp>
#include <sge/input/focus/event/key_repeat.hpp>
#include <sge/input/focus/event/out.hpp>
#include <sge/input/focus/event/remove.hpp>
#include <sge/input/focus/event/text.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/axis_code_to_string.hpp>
#include <sge/input/joypad/button_info.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/device.hpp>
#include <sge/input/joypad/info.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/absolute_axis.hpp>
#include <sge/input/joypad/event/button.hpp>
#include <sge/input/joypad/event/discover.hpp>
#include <sge/input/joypad/event/relative_axis.hpp>
#include <sge/input/joypad/event/remove.hpp>
#include <sge/input/joypad/ff/type.hpp>
#include <sge/input/joypad/ff/type_to_string.hpp>
#include <sge/input/key/code_to_string.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/keyboard/event/discover.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/input/keyboard/event/remove.hpp>
#include <sge/input/mouse/axis_code_to_string.hpp>
#include <sge/input/mouse/axis_info.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_code_to_string.hpp>
#include <sge/input/mouse/button_info.hpp>
#include <sge/input/mouse/button_info_container.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/axis.hpp>
#include <sge/input/mouse/event/button.hpp>
#include <sge/input/mouse/event/discover.hpp>
#include <sge/input/mouse/event/remove.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/display_mode/desired_fps.hpp>
#include <sge/renderer/display_mode/object.hpp>
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
#include <sge/renderer/target/viewport.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_font.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/timer/scoped_frame_limiter.hpp>
#include <sge/viewport/fill_on_resize.hpp>
#include <sge/viewport/manage_callback.hpp>
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
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_wstring.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/reference.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/shared_ptr_output.hpp>
#include <fcppt/string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/enum/make_range.hpp>
#include <fcppt/io/cout.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/box/null.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/optional_short_name.hpp>
#include <fcppt/options/parse.hpp>
#include <fcppt/options/result.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/options/switch.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <exception>
#include <ostream>
#include <fcppt/config/external_end.hpp>

namespace
{

fcppt::string output_optional_string(fcppt::optional_string const &);

fcppt::string output_optional_position(sge::input::cursor::optional_position const &);

void cursor_new(sge::input::cursor::object const &);

void cursor_discover(fcppt::reference<sge::input::cursor::event::discover const>);

void cursor_remove(fcppt::reference<sge::input::cursor::event::remove const>);

void cursor_button(fcppt::reference<sge::input::cursor::event::button const>);

void cursor_move(fcppt::reference<sge::input::cursor::event::move const>);

void cursor_scroll(fcppt::reference<sge::input::cursor::event::scroll const>);

void focus_new(sge::input::focus::object const &);

void focus_discover(fcppt::reference<sge::input::focus::event::discover const>);

void focus_remove(fcppt::reference<sge::input::focus::event::remove const>);

void focus_text(fcppt::reference<sge::input::focus::event::text const>);

void focus_key(fcppt::reference<sge::input::focus::event::key const>);

void focus_key_repeat(fcppt::reference<sge::input::focus::event::key_repeat const>);

void focus_in(fcppt::reference<sge::input::focus::event::in const>);

void focus_out(fcppt::reference<sge::input::focus::event::out const>);

void joypad_new(sge::input::joypad::device const &);

void joypad_discover(fcppt::reference<sge::input::joypad::event::discover const>);

void joypad_remove(fcppt::reference<sge::input::joypad::event::remove const>);

void joypad_absolute_axis(fcppt::reference<sge::input::joypad::event::absolute_axis const>);

void joypad_button(fcppt::reference<sge::input::joypad::event::button const>);

void joypad_relative_axis(fcppt::reference<sge::input::joypad::event::relative_axis const>);

void keyboard_new(sge::input::keyboard::device const &);

void keyboard_discover(fcppt::reference<sge::input::keyboard::event::discover const>);

void keyboard_remove(fcppt::reference<sge::input::keyboard::event::remove const>);

void keyboard_key(fcppt::reference<sge::input::keyboard::event::key const>);

void mouse_new(sge::input::mouse::device const &);

void mouse_discover(fcppt::reference<sge::input::mouse::event::discover const>);

void mouse_remove(fcppt::reference<sge::input::mouse::event::remove const>);

void mouse_axis(fcppt::reference<sge::input::mouse::event::axis const>);

void mouse_button(fcppt::reference<sge::input::mouse::event::button const>);

FCPPT_RECORD_MAKE_LABEL(silent_label);

using silent_switch = fcppt::options::switch_<silent_label>;

using options_result = fcppt::options::result_of<silent_switch>;

awl::main::exit_code input_main(options_result const &);

void draw(
    sge::renderer::device::ffp &, // NOLINT(google-runtime-references)
    sge::console::gfx::object & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

void handle_events(
    sge::renderer::device::ffp &, // NOLINT(google-runtime-references)
    sge::console::gfx::object &, // NOLINT(google-runtime-references)
    awl::event::base const &);

}

awl::main::exit_code example_main(awl::main::function_context const &_context)
try
{
  silent_switch const args_parser{
      fcppt::options::optional_short_name{},
      fcppt::options::long_name{FCPPT_TEXT("silent")},
      fcppt::options::optional_help_text{}};

  fcppt::options::result<options_result> const result{fcppt::options::parse(
      args_parser, fcppt::args_from_second(_context.argc(), _context.argv()))};

  return fcppt::either::match(
      result,
      [](fcppt::options::error const &_error)
      {
        awl::show_error(fcppt::output_to_fcppt_string(_error));

        return awl::main::exit_failure();
      },
      [](options_result const &_result) { return input_main(_result); });
}
catch (fcppt::exception const &_exception)
{
  awl::show_error(_exception.string());

  return awl::main::exit_failure();
}
catch (std::exception const &_exception)
{
  awl::show_error_narrow(_exception.what());

  return awl::main::exit_failure();
}

namespace
{

awl::main::exit_code input_main(options_result const &_args)
{
  bool const silent{fcppt::record::get<silent_label>(_args)};

  sge::systems::instance<
      sge::systems::with_window,
      sge::systems::with_renderer<sge::systems::renderer_caps::ffp>,
      sge::systems::with_input,
      sge::systems::with_font> const
      sys(sge::systems::make_list(sge::systems::window(sge::systems::window_source(
          sge::systems::original_window(sge::window::title(FCPPT_TEXT("sge input example"))))))(
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
          sge::systems::input(
              sge::systems::cursor_option_field{sge::systems::cursor_option::exclusive}))(
          sge::systems::config().log_settings(
              sge::systems::log_settings(sge::log::option_container{sge::log::option{
                  sge::input::log_location(),
                  silent ? fcppt::log::level::error : fcppt::log::level::debug}}))));

  sge::console::object console(sge::console::prefix(SGE_FONT_LIT('/')));

  sge::console::muxing_fcppt_streambuf muxing_streambuf(
      fcppt::make_ref(fcppt::io::cout()), fcppt::make_ref(console), sge::console::muxing::enabled);

  sge::font::object_unique_ptr const font(sys.font_system().create_font(sge::font::parameters()));

  sge::console::gfx::object console_gfx(
      fcppt::make_ref(console),
      fcppt::make_ref(sys.renderer_device_ffp()),
      sge::console::gfx::font_color(
          sge::image::color::any::object{sge::image::color::predef::white()}),
      fcppt::make_ref(*font),
      fcppt::math::box::null<sge::font::rect>(),
      sge::console::gfx::output_line_limit(
          200U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
          ));

  fcppt::signal::auto_connection const console_resize_con(
      sys.viewport_manager().manage_callback(sge::viewport::manage_callback{
          [&console_gfx](sge::renderer::target::viewport const &_viewport)
          {
            console_gfx.area(sge::font::rect{
                fcppt::math::vector::null<sge::font::rect::vector>(),
                fcppt::math::dim::structure_cast<sge::font::rect::dim, fcppt::cast::size_fun>(
                    _viewport.get().size())});
          }}));

  fcppt::io::cout() << std::boolalpha;

  for (sge::input::cursor::shared_ptr const &cursor : sys.input_processor().cursors())
  {
    cursor_new(*cursor);
  }

  for (sge::input::focus::shared_ptr const &focus : sys.input_processor().foci())
  {
    focus_new(*focus);
  }

  for (sge::input::joypad::shared_ptr const &joypad : sys.input_processor().joypads())
  {
    joypad_new(*joypad);
  }

  for (sge::input::keyboard::shared_ptr const &keyboard : sys.input_processor().keyboards())
  {
    keyboard_new(*keyboard);
  }

  for (sge::input::mouse::shared_ptr const &mouse : sys.input_processor().mice())
  {
    mouse_new(*mouse);
  }

  return sge::window::loop(
      sys.window_system(),
      sge::window::loop_function{[&sys, &console_gfx](awl::event::base const &_event) {
        handle_events(sys.renderer_device_ffp(), console_gfx, _event);
      }});
}

void handle_events(
    sge::renderer::device::ffp &_renderer_device,
    sge::console::gfx::object &_console_gfx,
    awl::event::base const &_event)
{
  fcppt::optional::maybe_void(
      fcppt::variant::dynamic_cast_<
          fcppt::mpl::list::object<
              sge::renderer::event::render const,
              sge::input::cursor::event::discover const,
              sge::input::cursor::event::remove const,
              sge::input::cursor::event::button const,
              sge::input::cursor::event::move const,
              sge::input::cursor::event::scroll const,
              sge::input::focus::event::discover const,
              sge::input::focus::event::remove const,
              sge::input::focus::event::text const,
              sge::input::focus::event::key const,
              sge::input::focus::event::key_repeat const,
              sge::input::focus::event::in const,
              sge::input::focus::event::out const,
              sge::input::joypad::event::discover const,
              sge::input::joypad::event::remove const,
              sge::input::joypad::event::absolute_axis const,
              sge::input::joypad::event::button const,
              sge::input::joypad::event::relative_axis const,
              sge::input::keyboard::event::discover const,
              sge::input::keyboard::event::remove const,
              sge::input::keyboard::event::key const,
              sge::input::mouse::event::discover const,
              sge::input::mouse::event::remove const,
              sge::input::mouse::event::axis const,
              sge::input::mouse::event::button const>,
          fcppt::cast::dynamic_fun>(_event),
      [&_console_gfx, &_renderer_device](auto const &_variant)
      {
        fcppt::variant::match(
            _variant,
            [&_console_gfx, &_renderer_device](fcppt::reference<sge::renderer::event::render const>)
            { return draw(_renderer_device, _console_gfx); },
            &cursor_discover,
            &cursor_remove,
            &cursor_button,
            &cursor_move,
            &cursor_scroll,
            &focus_discover,
            &focus_remove,
            &focus_text,
            &focus_key,
            &focus_key_repeat,
            &focus_in,
            &focus_out,
            &joypad_discover,
            &joypad_remove,
            &joypad_absolute_axis,
            &joypad_button,
            &joypad_relative_axis,
            &keyboard_discover,
            &keyboard_remove,
            &keyboard_key,
            &mouse_discover,
            &mouse_remove,
            &mouse_axis,
            &mouse_button);
      });
}

void draw(sge::renderer::device::ffp &_renderer_device, sge::console::gfx::object &_console_gfx)
{
  sge::timer::scoped_frame_limiter const limiter(
      sge::renderer::display_mode::desired_fps(_renderer_device.display_mode()));

  sge::renderer::context::scoped_ffp const scoped_ffp(
      fcppt::make_ref(_renderer_device),
      fcppt::reference_to_base<sge::renderer::target::base>(
          fcppt::make_ref(_renderer_device.onscreen_target())));

  scoped_ffp.get().clear(sge::renderer::clear::parameters().back_buffer(
      sge::image::color::any::object{sge::image::color::predef::black()}));

  _console_gfx.render(scoped_ffp.get(), sge::console::gfx::input_active{false});
}

fcppt::string output_optional_string(fcppt::optional_string const &_name)
{
  return fcppt::optional::from(_name, [] { return fcppt::string(FCPPT_TEXT("unnamed")); });
}

fcppt::string output_optional_position(sge::input::cursor::optional_position const &_opt_position)
{
  return fcppt::optional::maybe(
      _opt_position,
      [] { return fcppt::string(FCPPT_TEXT("none")); },
      [](sge::input::cursor::position const &_position)
      { return fcppt::output_to_fcppt_string(_position); });
}

void cursor_new(sge::input::cursor::object const &_cursor)
{
  fcppt::io::cout() << FCPPT_TEXT("cursor_discover: ") << &_cursor << FCPPT_TEXT('\n');
}

void cursor_discover(fcppt::reference<sge::input::cursor::event::discover const> const _event)
{
  cursor_new(*_event.get().cursor());
}

void cursor_remove(fcppt::reference<sge::input::cursor::event::remove const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("cursor_remove: ") << _event.get().cursor() << FCPPT_TEXT('\n');
}

void cursor_button(fcppt::reference<sge::input::cursor::event::button const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("cursor_button: ") << _event.get().cursor()
                    << FCPPT_TEXT("\n\tcode: ")
                    << sge::input::cursor::button_code_to_string(_event.get().button_code())
                    << FCPPT_TEXT("\n\tposition: ") << _event.get().position()
                    << FCPPT_TEXT("\n\tpressed: ") << _event.get().pressed() << FCPPT_TEXT('\n');
}

void cursor_move(fcppt::reference<sge::input::cursor::event::move const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("cursor_move: ") << _event.get().cursor()
                    << FCPPT_TEXT("\n\tposition: ")
                    << output_optional_position(_event.get().position()) << FCPPT_TEXT('\n');
}

void cursor_scroll(fcppt::reference<sge::input::cursor::event::scroll const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("cursor_scroll: ") << _event.get().cursor()
                    << FCPPT_TEXT("\n\tcode: ")
                    << sge::input::cursor::scroll_code_to_string(_event.get().code())
                    << FCPPT_TEXT("\n\tdelta: ") << _event.get().value() << FCPPT_TEXT('\n');
}

void focus_new(sge::input::focus::object const &_focus)
{
  fcppt::io::cout() << FCPPT_TEXT("focus_discover: ") << &_focus << FCPPT_TEXT('\n');
}

void focus_discover(fcppt::reference<sge::input::focus::event::discover const> const _event)
{
  focus_new(*_event.get().focus());
}

void focus_remove(fcppt::reference<sge::input::focus::event::remove const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("focus_remove: ") << _event.get().focus() << FCPPT_TEXT('\n');
}

void focus_text(fcppt::reference<sge::input::focus::event::text const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("focus_text: ") << _event.get().focus()
                    << FCPPT_TEXT("\n\ttext: ")
                    << fcppt::optional::from(
                           fcppt::from_std_wstring(_event.get().get()),
                           []
                           { return fcppt::string{FCPPT_TEXT("Failed to convert focus text!")}; })
                    << FCPPT_TEXT('\n');
}

void focus_key(fcppt::reference<sge::input::focus::event::key const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("focus_key: ") << _event.get().focus()
                    << FCPPT_TEXT("\n\tkey_code: ")
                    << sge::input::key::code_to_string(_event.get().get().code())
                    << FCPPT_TEXT("\n\tpressed: ") << _event.get().pressed() << FCPPT_TEXT('\n');
}

void focus_key_repeat(fcppt::reference<sge::input::focus::event::key_repeat const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("focus_key_repeat: ") << _event.get().focus()
                    << FCPPT_TEXT("\n\tkey_code: ")
                    << sge::input::key::code_to_string(_event.get().key().code())
                    << FCPPT_TEXT('\n');
}

void focus_in(fcppt::reference<sge::input::focus::event::in const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("focus_in: ") << _event.get().focus() << FCPPT_TEXT('\n');
}

void focus_out(fcppt::reference<sge::input::focus::event::out const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("focus_out: ") << _event.get().focus() << FCPPT_TEXT('\n');
}

void joypad_new(sge::input::joypad::device const &_joypad)
{
  sge::input::joypad::info const info(_joypad.info());

  fcppt::io::cout() << FCPPT_TEXT("joypad_discover: ") << &_joypad << FCPPT_TEXT(", ")
                    << info.name() << FCPPT_TEXT(", ") << info.unique_id() << FCPPT_TEXT('\n');

  {
    sge::input::joypad::absolute_axis_info_container::vector const &absolute_axes(
        info.absolute_axes().get());

    fcppt::io::cout() << FCPPT_TEXT("\tabsolute axes: ") << absolute_axes.size()
                      << FCPPT_TEXT('\n');

    for (sge::input::joypad::absolute_axis_info const &axis_info : absolute_axes)
    {
      fcppt::io::cout() << FCPPT_TEXT("\t\tname: ") << output_optional_string(axis_info.name())
                        << FCPPT_TEXT("\n\t\tcode: ")
                        << sge::input::joypad::axis_code_to_string(axis_info.code())
                        << FCPPT_TEXT("\n\t\tmin: ") << axis_info.min() << FCPPT_TEXT("\n\t\tmax: ")
                        << axis_info.max() << FCPPT_TEXT('\n');
    }
  }

  {
    sge::input::joypad::relative_axis_info_container::vector const &relative_axes(
        info.relative_axes().get());

    fcppt::io::cout() << FCPPT_TEXT("\trelative axes: ") << relative_axes.size()
                      << FCPPT_TEXT('\n');

    for (sge::input::joypad::relative_axis_info const &axis_info : relative_axes)
    {
      fcppt::io::cout() << FCPPT_TEXT("\t\tname: ") << output_optional_string(axis_info.name())
                        << FCPPT_TEXT("\n\t\tcode: ")
                        << sge::input::joypad::axis_code_to_string(axis_info.code())
                        << FCPPT_TEXT('\n');
    }
  }

  {
    sge::input::joypad::button_info_container::vector const &buttons(info.buttons().get());

    fcppt::io::cout() << FCPPT_TEXT("\tbuttons: ") << buttons.size() << FCPPT_TEXT('\n');

    for (sge::input::joypad::button_info const &button_info : buttons)
    {
      fcppt::io::cout() << FCPPT_TEXT("\t\tname: ") << output_optional_string(button_info.name())
                        << FCPPT_TEXT('\n');
    }
  }

  {
    fcppt::io::cout() << FCPPT_TEXT("\tff effects:\n");

    for (sge::input::joypad::ff::type const effect :
         fcppt::enum_::make_range<sge::input::joypad::ff::type>())
    {
      if (info.ff_types() & effect)
      {
        fcppt::io::cout() << FCPPT_TEXT("\t\t ") << sge::input::joypad::ff::type_to_string(effect)
                          << FCPPT_TEXT('\n');
      }
    }
  }
}

void joypad_discover(fcppt::reference<sge::input::joypad::event::discover const> const _event)
{
  joypad_new(*_event.get().joypad());
}

void joypad_remove(fcppt::reference<sge::input::joypad::event::remove const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("joypad_remove: ") << _event.get().joypad() << FCPPT_TEXT('\n');
}

void joypad_absolute_axis(
    fcppt::reference<sge::input::joypad::event::absolute_axis const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("joypad_absolute_axis: ") << _event.get().joypad()
                    << FCPPT_TEXT("\n\tcode: ")
                    << sge::input::joypad::axis_code_to_string(_event.get().axis().code())
                    << FCPPT_TEXT("\n\tid: ") << _event.get().axis().id()
                    << FCPPT_TEXT("\n\tvalue: ") << _event.get().value() << FCPPT_TEXT('\n');
}

void joypad_button(fcppt::reference<sge::input::joypad::event::button const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("joypad_button: ") << _event.get().joypad()
                    << FCPPT_TEXT("\n\tid: ") << _event.get().button_id()
                    << FCPPT_TEXT("\n\tpressed: ") << _event.get().pressed() << FCPPT_TEXT('\n');
}

void joypad_relative_axis(
    fcppt::reference<sge::input::joypad::event::relative_axis const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("joypad_relative_axis: ") << _event.get().joypad()
                    << FCPPT_TEXT("\n\tcode: ")
                    << sge::input::joypad::axis_code_to_string(_event.get().axis().code())
                    << FCPPT_TEXT("\n\tid: ") << _event.get().axis().id()
                    << FCPPT_TEXT("\n\tvalue: ") << _event.get().value() << FCPPT_TEXT('\n');
}

void keyboard_new(sge::input::keyboard::device const &_keyboard)
{
  fcppt::io::cout() << FCPPT_TEXT("keyboard_discover: ") << &_keyboard << FCPPT_TEXT('\n');
}

void keyboard_discover(fcppt::reference<sge::input::keyboard::event::discover const> const _event)
{
  keyboard_new(*_event.get().keyboard());
}

void keyboard_remove(fcppt::reference<sge::input::keyboard::event::remove const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("keyboard_remove: ") << _event.get().keyboard()
                    << FCPPT_TEXT('\n');
}

void keyboard_key(fcppt::reference<sge::input::keyboard::event::key const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("keyboard_key: ") << _event.get().keyboard()
                    << FCPPT_TEXT("\n\tid: ") << _event.get().get().id()
                    << FCPPT_TEXT("\n\tkey_code: ")
                    << sge::input::key::code_to_string(_event.get().get().code())
                    << FCPPT_TEXT("\n\tpressed: ") << _event.get().pressed() << FCPPT_TEXT('\n');
}

void mouse_new(sge::input::mouse::device const &_mouse)
{
  sge::input::mouse::info const info(_mouse.info());

  fcppt::io::cout() << FCPPT_TEXT("mouse_discover: ") << &_mouse << FCPPT_TEXT(", ") << info.name()
                    << FCPPT_TEXT('\n');

  {
    sge::input::mouse::axis_info_container::vector const &axes(info.axes().get());

    fcppt::io::cout() << FCPPT_TEXT("\taxes: ") << axes.size() << FCPPT_TEXT('\n');

    for (sge::input::mouse::axis_info const &axis_info : axes)
    {
      fcppt::io::cout() << FCPPT_TEXT("\t\tname: ") << output_optional_string(axis_info.name())
                        << FCPPT_TEXT("\n\t\tcode: ")
                        << sge::input::mouse::axis_code_to_string(axis_info.code())
                        << FCPPT_TEXT('\n');
    }
  }

  {
    sge::input::mouse::button_info_container::vector const &buttons(info.buttons().get());

    fcppt::io::cout() << FCPPT_TEXT("\tbuttons: ") << buttons.size() << FCPPT_TEXT('\n');

    for (sge::input::mouse::button_info const &button_info : buttons)
    {
      fcppt::io::cout() << FCPPT_TEXT("\t\tname: ") << output_optional_string(button_info.name())
                        << FCPPT_TEXT("\n\t\tcode: ")
                        << sge::input::mouse::button_code_to_string(button_info.code())
                        << FCPPT_TEXT('\n');
    }
  }
}

void mouse_discover(fcppt::reference<sge::input::mouse::event::discover const> const _event)
{
  mouse_new(*_event.get().mouse());
}

void mouse_remove(fcppt::reference<sge::input::mouse::event::remove const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("mouse_remove: ") << _event.get().mouse() << FCPPT_TEXT('\n');
}

void mouse_axis(fcppt::reference<sge::input::mouse::event::axis const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("mouse_axis: ") << _event.get().mouse()
                    << FCPPT_TEXT("\n\tcode: ")
                    << sge::input::mouse::axis_code_to_string(_event.get().get().code())
                    << FCPPT_TEXT("\n\tid: ") << _event.get().get().id()
                    << FCPPT_TEXT("\n\tvalue: ") << _event.get().value() << FCPPT_TEXT('\n');
}

void mouse_button(fcppt::reference<sge::input::mouse::event::button const> const _event)
{
  fcppt::io::cout() << FCPPT_TEXT("mouse_button: ") << _event.get().mouse()
                    << FCPPT_TEXT("\n\tcode: ")
                    << sge::input::mouse::button_code_to_string(_event.get().get().code())
                    << FCPPT_TEXT("\n\tid: ") << _event.get().get().id()
                    << FCPPT_TEXT("\n\tpressed: ") << _event.get().pressed() << FCPPT_TEXT('\n');
}

}
