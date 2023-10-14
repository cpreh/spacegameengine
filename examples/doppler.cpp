//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/file.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/listener.hpp>
#include <sge/audio/load_exn.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/position.hpp>
#include <sge/audio/scalar.hpp>
#include <sge/audio/vector.hpp>
#include <sge/audio/vector2.hpp>
#include <sge/audio/vector2_to_vector.hpp>
#include <sge/audio/sound/positional.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/sound/positional_parameters.hpp>
#include <sge/audio/sound/positional_unique_ptr.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sge/config/media_path.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <sge/input/cursor/relative_movement/event.hpp>
#include <sge/input/cursor/relative_movement/object.hpp>
#include <sge/log/location.hpp>
#include <sge/log/option.hpp>
#include <sge/log/option_container.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/pixel_unit.hpp>
#include <sge/renderer/resource_flags_field.hpp>
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
#include <sge/renderer/target/onscreen.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/target/viewport.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb_from_caps.hpp>
#include <sge/renderer/texture/planar.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/object.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single.hpp>
#include <sge/sprite/buffers/with_declaration.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/sprite/roles/pos_or_center.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object.hpp>
#include <sge/sprite/state/parameters.hpp>
#include <sge/systems/audio_loader.hpp>
#include <sge/systems/audio_player_default.hpp>
#include <sge/systems/config.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/input.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/original_window.hpp>
#include <sge/systems/quit_on_escape.hpp>
#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/window_source.hpp>
#include <sge/systems/with_audio_loader.hpp>
#include <sge/systems/with_audio_player.hpp>
#include <sge/systems/with_image2d.hpp>
#include <sge/systems/with_input.hpp>
#include <sge/systems/with_renderer.hpp>
#include <sge/systems/with_window.hpp>
#include <sge/texture/const_part_unique_ptr.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/part_raw_ptr.hpp>
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
#include <awl/main/function_context_fwd.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/unique_ptr_to_const.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/cast/int_to_float_fun.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/log/level.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <example_main.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>

awl::main::exit_code example_main(awl::main::function_context const &)
try
{
  sge::systems::instance<
      sge::systems::with_renderer<sge::systems::renderer_caps::ffp>,
      sge::systems::with_window,
      sge::systems::with_input,
      sge::systems::with_audio_player,
      sge::systems::with_audio_loader,
      sge::systems::with_image2d> const
      sys(sge::systems::make_list(sge::systems::window(sge::systems::window_source(
          sge::systems::original_window(sge::window::title(FCPPT_TEXT("sge dopplertest"))))))(
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
          sge::systems::input(sge::systems::cursor_option_field::null()))(
          sge::systems::audio_player_default())(
          sge::systems::image2d(sge::media::optional_extension_set(
              sge::media::extension_set{sge::media::extension(FCPPT_TEXT("png"))})))(
          sge::systems::audio_loader(sge::media::optional_extension_set(
              sge::media::extension_set{sge::media::extension(FCPPT_TEXT("ogg"))})))(
          sge::systems::config().log_settings(sge::systems::log_settings(sge::log::option_container{
              sge::log::option{sge::log::location(), fcppt::log::level::debug}}))));

  sge::texture::const_part_unique_ptr const tex_bg(
      fcppt::unique_ptr_to_const(fcppt::unique_ptr_to_base<sge::texture::part>(
          fcppt::make_unique_ptr<sge::texture::part_raw_ptr>(
              sge::renderer::texture::create_planar_from_path(
                  sge::config::media_path() / FCPPT_TEXT("images") / FCPPT_TEXT("grass.png"),
                  fcppt::make_ref(sys.renderer_device_core()),
                  sys.image_system(),
                  sge::renderer::texture::mipmap::off(),
                  sge::renderer::resource_flags_field::null(),
                  sge::renderer::texture::emulate_srgb_from_caps(
                      sys.renderer_device_ffp().caps()))))));

  sge::texture::const_part_unique_ptr const tex_tux(
      fcppt::unique_ptr_to_const(fcppt::unique_ptr_to_base<sge::texture::part>(
          fcppt::make_unique_ptr<sge::texture::part_raw_ptr>(
              sge::renderer::texture::create_planar_from_path(
                  sge::config::media_path() / FCPPT_TEXT("images") / FCPPT_TEXT("tux.png"),
                  fcppt::make_ref(sys.renderer_device_core()),
                  sys.image_system(),
                  sge::renderer::texture::mipmap::off(),
                  sge::renderer::resource_flags_field::null(),
                  sge::renderer::texture::emulate_srgb_from_caps(
                      sys.renderer_device_ffp().caps()))))));

  using sprite_choices = sge::sprite::config::choices<
      sge::sprite::config::type_choices<
          sge::sprite::config::unit_type<sge::renderer::pixel_unit>,
          sge::sprite::config::float_type<float>>,
      sge::sprite::config::pos<sge::sprite::config::pos_option::pos_or_center>,
      sge::sprite::config::normal_size<sge::sprite::config::texture_size_option::always>,
      fcppt::mpl::list::object<sge::sprite::config::with_texture<
          sge::sprite::config::texture_level_count<1U>,
          sge::sprite::config::texture_coordinates::automatic,
          sge::sprite::config::texture_ownership::reference>>>;

  using sprite_object = sge::sprite::object<sprite_choices>;

  using sprite_buffers =
      sge::sprite::buffers::with_declaration<sge::sprite::buffers::single<sprite_choices>>;

  using sprite_state_choices = sge::sprite::state::all_choices;

  using sprite_state_object = sge::sprite::state::object<sprite_state_choices>;

  using sprite_state_parameters = sge::sprite::state::parameters<sprite_state_choices>;

  sprite_buffers sprite_buf(
      fcppt::make_ref(sys.renderer_device_core()), sge::sprite::buffers::option::dynamic);

  sprite_state_object sprite_states(
      fcppt::make_ref(sys.renderer_device_ffp()), sprite_state_parameters());

  sprite_object background(
      sge::sprite::roles::texture0{} = sprite_object::texture_type(*tex_bg),
      sge::sprite::roles::pos_or_center{} = sprite_object::pos_or_center_type(
          sprite_object::pos_type(fcppt::math::vector::null<sprite_object::vector>())));

  sprite_object tux(
      sge::sprite::roles::pos_or_center{} =
          sprite_object::pos_or_center_type(sprite_object::center_type(background.center())),
      sge::sprite::roles::texture0{} = sprite_object::texture_type(*tex_tux));

  sge::audio::file_unique_ptr const af_siren(sge::audio::load_exn(
      fcppt::make_ref(sys.audio_loader()),
      sge::config::media_path() / FCPPT_TEXT("sounds") / FCPPT_TEXT("siren.ogg")));

  sge::audio::sound::positional_unique_ptr const sound_siren(
      sys.audio_player().create_positional_stream(
          fcppt::make_ref(*af_siren),
          sge::audio::sound::positional_parameters(
              // TODO(philipp): Improve this
              sge::audio::position{fcppt::math::vector::null<sge::audio::vector>()})
              .rolloff_factor(
                  fcppt::literal<sge::audio::scalar>(1) /
                  fcppt::literal<sge::audio::scalar>(
                      500 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                      ))));

  fcppt::signal::auto_connection const viewport_connection{
      sys.viewport_manager().manage_callback(sge::viewport::manage_callback{
          [&sys, &tux, &background](sge::renderer::target::viewport const &_viewport)
          {
            auto const center(fcppt::math::dim::to_vector(
                fcppt::math::dim::structure_cast<sprite_object::dim, fcppt::cast::size_fun>(
                    (_viewport.get().size() / fcppt::literal<sge::renderer::pixel_unit>(2))
                        .get_unsafe())));

            sys.audio_player().listener().position(sge::audio::vector2_to_vector(
                fcppt::math::vector::
                    structure_cast<sge::audio::vector2, fcppt::cast::int_to_float_fun>(center)));

            tux.center(center);

            background.center(center);
          }})};

  sys.audio_player().speed_of_sound(fcppt::literal<sge::audio::scalar>(
      500 // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      ));

  sound_siren->play(sge::audio::sound::repeat::loop);

  auto const on_move(
      [&sound_siren](sge::input::cursor::event::move const &_event)
      {
        fcppt::optional::maybe_void(
            _event.position(),
            [&sound_siren](sge::input::cursor::position const &_pos)
            {
              sound_siren->position(sge::audio::vector2_to_vector(
                  fcppt::math::vector::
                      structure_cast<sge::audio::vector2, fcppt::cast::int_to_float_fun>(_pos)));
            });
      });

  sge::input::cursor::relative_movement::object rel_movement{
      fcppt::make_ref(sys.input_processor())};

  auto const on_rel_move(
      [&sound_siren](sge::input::cursor::relative_movement::event const &_event)
      {
        sound_siren->linear_velocity(sge::audio::vector2_to_vector(
            fcppt::math::vector::structure_cast<sge::audio::vector2, fcppt::cast::int_to_float_fun>(
                _event.difference().get())));
      });

  auto const draw(
      [&background, &sound_siren, &sprite_buf, &sprite_states, &sys, &tux]
      {
        sge::renderer::context::scoped_ffp const scoped_block(
            fcppt::make_ref(sys.renderer_device_ffp()),
            fcppt::reference_to_base<sge::renderer::target::base>(
                fcppt::make_ref(sys.renderer_device_ffp().onscreen_target())));

        scoped_block.get().clear(sge::renderer::clear::parameters().back_buffer(
            sge::image::color::any::object{sge::image::color::predef::black()}));

        sge::sprite::process::one(scoped_block.get(), background, sprite_buf, sprite_states);

        sge::sprite::process::one(scoped_block.get(), tux, sprite_buf, sprite_states);

        sound_siren->update();
      });

  return sge::window::loop(
      sys.window_system(),
      sge::window::loop_function{
          [&sys, &on_move, &on_rel_move, &draw](awl::event::base const &_event)
          {
            sge::systems::quit_on_escape(sys, _event);

            fcppt::optional::maybe_void(
                fcppt::variant::dynamic_cast_<
                    fcppt::mpl::list::object<
                        sge::input::cursor::event::move const,
                        sge::input::cursor::relative_movement::event const,
                        sge::renderer::event::render const>,
                    fcppt::cast::dynamic_fun>(_event),
                [&on_move, &on_rel_move, &draw](auto const &_variant)
                {
                  fcppt::variant::match(
                      _variant,
                      [&on_move](
                          fcppt::reference<sge::input::cursor::event::move const> const _move_event)
                      { on_move(_move_event.get()); },
                      [&on_rel_move](
                          fcppt::reference<sge::input::cursor::relative_movement::event const> const
                              _relative_movement) { on_rel_move(_relative_movement.get()); },
                      [&draw](fcppt::reference<sge::renderer::event::render const>) { draw(); });
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
