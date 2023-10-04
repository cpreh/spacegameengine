//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/audio/loader_fwd.hpp>
#include <sge/audio/player_fwd.hpp>
#include <sge/audio/loader_plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/loader_plugin/manager.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/player_plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/audio/player_plugin/manager.hpp> // NOLINT(misc-include-cleaner)
#include <sge/font/system_fwd.hpp>
#include <sge/font/plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/font/plugin/manager.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/system_fwd.hpp>
#include <sge/image2d/plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/image2d/plugin/manager.hpp> // NOLINT(misc-include-cleaner)
#include <sge/input/processor_fwd.hpp>
#include <sge/input/system_fwd.hpp>
#include <sge/input/plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/input/plugin/manager.hpp> // NOLINT(misc-include-cleaner)
#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/parse/ini/optional_start_fwd.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/renderer/core_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/plugin/collection.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/plugin/manager.hpp> // NOLINT(misc-include-cleaner)
#include <sge/systems/audio_loader_fwd.hpp>
#include <sge/systems/audio_player_fwd.hpp>
#include <sge/systems/exception.hpp>
#include <sge/systems/font_fwd.hpp>
#include <sge/systems/image2d_fwd.hpp>
#include <sge/systems/input_fwd.hpp>
#include <sge/systems/optional_log_context_ref_fwd.hpp>
#include <sge/systems/plugin_path.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <sge/systems/impl/log_name.hpp>
#include <sge/systems/impl/audio/loader.hpp>
#include <sge/systems/impl/audio/player.hpp>
#include <sge/systems/impl/detail/instance_impl.hpp>
#include <sge/systems/impl/font/object.hpp>
#include <sge/systems/impl/image2d/object.hpp>
#include <sge/systems/impl/input/object.hpp>
#include <sge/systems/impl/renderer/device.hpp>
#include <sge/systems/impl/renderer/system.hpp>
#include <sge/systems/impl/window/object.hpp>
#include <sge/systems/impl/window/object_unique_ptr.hpp>
#include <sge/systems/impl/window/system.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::systems::detail::instance_impl::instance_impl(
    sge::systems::plugin_path const &_plugin_path,
    sge::systems::optional_log_context_ref const &_log_context)
    : log_context_{_log_context},
      log_{
          this->log_context(),
          sge::log::location(),
          sge::log::default_parameters(sge::systems::impl::log_name())},
      plugin_cache_(),
      plugin_manager_(
          this->log_context(),
          _plugin_path.get(),
          sge::plugin::optional_cache_ref(fcppt::make_ref(plugin_cache_))),
      window_system_(),
      renderer_system_(),
      window_object_(),
      renderer_device_(),
      input_(),
      audio_loader_(),
      audio_player_(),
      image2d_(),
      font_()
{
}

FCPPT_PP_POP_WARNING

sge::systems::detail::instance_impl::~instance_impl() = default;

void sge::systems::detail::instance_impl::init_window_system(
    sge::systems::window const &_parameters)
{
  window_system_ = optional_window_system(
      fcppt::make_unique_ptr<sge::systems::impl::window::system>(this->log_context(), _parameters));
}

void sge::systems::detail::instance_impl::init_renderer_system(
    sge::systems::detail::renderer const &_parameters,
    sge::parse::ini::optional_start const &_config)
{
  renderer_system_ =
      optional_renderer_system{fcppt::make_unique_ptr<sge::systems::impl::renderer::system>(
          this->log_context(),
          plugin_manager_.collection<sge::renderer::core>(),
          _parameters,
          _config,
          *fcppt::optional::to_exception(
              this->window_system_,
              []
              { return sge::systems::exception{FCPPT_TEXT("Window system not initialized!")}; }))};
}

void sge::systems::detail::instance_impl::init_window_object(
    sge::systems::window const &_parameters)
{
  window_object_ =
      optional_window_object(fcppt::make_unique_ptr<sge::systems::impl::window::object>(
          _parameters,
          *fcppt::optional::to_exception(
              this->window_system_,
              []
              { return sge::systems::exception{FCPPT_TEXT("Window system not initialized!")}; }),
          fcppt::optional::deref(renderer_system_)));
}

void sge::systems::detail::instance_impl::init_renderer(
    sge::systems::detail::renderer const &_param)
{
  renderer_device_ =
      optional_renderer_device{fcppt::make_unique_ptr<sge::systems::impl::renderer::device>(
          _param,
          *fcppt::optional::to_exception(
              this->renderer_system_,
              []
              { return sge::systems::exception{FCPPT_TEXT("Renderer system not initialized!")}; }),
          *fcppt::optional::to_exception(
              this->window_object_,
              []
              { return sge::systems::exception{FCPPT_TEXT("Window object not initialized!")}; }))};
}

void sge::systems::detail::instance_impl::init_input(sge::systems::input const &_parameters)
{
  input_ = optional_input{fcppt::make_unique_ptr<sge::systems::impl::input::object>(
      this->log_context(),
      log_,
      plugin_manager_.collection<sge::input::system>(),
      _parameters,
      *fcppt::optional::to_exception(
          this->window_object_,
          [] { return sge::systems::exception{FCPPT_TEXT("Window object not initialized!")}; }))};
}

void sge::systems::detail::instance_impl::init_image2d(sge::systems::image2d const &_parameters)
{
  image2d_ = optional_image2d(fcppt::make_unique_ptr<sge::systems::impl::image2d::object>(
      this->log_context(), plugin_manager_.collection<sge::image2d::system>(), _parameters));
}

void sge::systems::detail::instance_impl::init_audio_loader(
    sge::systems::audio_loader const &_parameters)
{
  audio_loader_ = optional_audio_loader(fcppt::make_unique_ptr<sge::systems::impl::audio::loader>(
      this->log_context(), plugin_manager_.collection<sge::audio::loader>(), _parameters));
}

void sge::systems::detail::instance_impl::init_audio_player(
    sge::systems::audio_player const &_parameters)
{
  audio_player_ = optional_audio_player(fcppt::make_unique_ptr<sge::systems::impl::audio::player>(
      this->log_context(), log_, plugin_manager_.collection<sge::audio::player>(), _parameters));
}

void sge::systems::detail::instance_impl::init_font(sge::systems::font const &_parameters)
{
  font_ = optional_font(fcppt::make_unique_ptr<sge::systems::impl::font::object>(
      this->log_context(), plugin_manager_.collection<sge::font::system>(), _parameters));
}

void sge::systems::detail::instance_impl::post_init()
{
  fcppt::optional::maybe_void(
      window_object_,
      [](sge::systems::impl::window::object_unique_ptr const &_window_object)
      { _window_object->post_init(); });
}

fcppt::log::context_reference sge::systems::detail::instance_impl::log_context()
{
  return log_context_.get();
}

fcppt::log::object &sge::systems::detail::instance_impl::log() { return log_; }

sge::plugin::manager &sge::systems::detail::instance_impl::plugin_manager()
{
  return plugin_manager_;
}

sge::renderer::core &sge::systems::detail::instance_impl::renderer_core() const
{
  return fcppt::optional::to_exception(
             this->renderer_system_,
             []{ return sge::systems::exception{FCPPT_TEXT("Renderer system initialized!")}; })
      ->core();
}

sge::renderer::system &sge::systems::detail::instance_impl::renderer_system() const
{
  return fcppt::optional::to_exception(
             this->renderer_system_,
             [] { return sge::systems::exception{FCPPT_TEXT("Renderer system initialized!")}; })
      ->get();
}

sge::renderer::device::ffp &sge::systems::detail::instance_impl::renderer_device_ffp() const
{
  return fcppt::optional::to_exception(
             this->renderer_device_,
             [] { return sge::systems::exception{FCPPT_TEXT("Renderer device initialized!")}; })
      ->get_ffp();
}

sge::renderer::device::core &sge::systems::detail::instance_impl::renderer_device_core() const
{
  return fcppt::optional::to_exception(
             this->renderer_device_,
             [] { return sge::systems::exception{FCPPT_TEXT("Renderer device initialized!")}; })
      ->get_core();
}

sge::input::system &sge::systems::detail::instance_impl::input_system() const
{
  return fcppt::optional::to_exception(
             this->input_,
             [] { return sge::systems::exception{FCPPT_TEXT("Input not initialized!")}; })
      ->system();
}

sge::input::processor &sge::systems::detail::instance_impl::input_processor() const
{
  return fcppt::optional::to_exception(
             this->input_,
             [] { return sge::systems::exception{FCPPT_TEXT("Input not initialized!")}; })
      ->processor();
}

sge::image2d::system &sge::systems::detail::instance_impl::image_system() const
{
  return fcppt::optional::to_exception(
             this->image2d_,
             [] { return sge::systems::exception{FCPPT_TEXT("Image2d not initialized!")}; })
      ->system();
}

sge::audio::loader &sge::systems::detail::instance_impl::audio_loader() const
{
  return fcppt::optional::to_exception(
             this->audio_loader_,
             [] { return sge::systems::exception{FCPPT_TEXT("Audio loader not initialized!")}; })
      ->get();
}

sge::audio::player &sge::systems::detail::instance_impl::audio_player() const
{
  return fcppt::optional::to_exception(
             this->audio_player_,
             [] { return sge::systems::exception{FCPPT_TEXT("Audio player not initialized!")}; })
      ->get();
}

sge::font::system &sge::systems::detail::instance_impl::font_system() const
{
  return fcppt::optional::to_exception(
             this->font_,
             [] { return sge::systems::exception{FCPPT_TEXT("Font not initialized!")}; })
      ->system();
}

sge::window::system &sge::systems::detail::instance_impl::window_system() const
{
  return fcppt::optional::to_exception(
             this->window_system_,
             [] { return sge::systems::exception{FCPPT_TEXT("Window system not initialized!")}; })
      ->get();
}

sge::window::object &sge::systems::detail::instance_impl::window() const
{
  return fcppt::optional::to_exception(
             this->window_object_,
             [] { return sge::systems::exception{FCPPT_TEXT("Window object not initialized!")}; })
      ->get();
}

sge::viewport::manager &sge::systems::detail::instance_impl::viewport_manager() const
{
  return fcppt::optional::to_exception(
             this->renderer_device_,
             [] { return sge::systems::exception{FCPPT_TEXT("Renderer device not initialized!")}; })
      ->viewport_manager();
}
