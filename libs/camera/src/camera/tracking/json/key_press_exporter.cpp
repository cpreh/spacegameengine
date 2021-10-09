//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/base.hpp>
#include <sge/camera/exception.hpp>
#include <sge/camera/impl/log_name.hpp>
#include <sge/camera/tracking/json/key_press_exporter.hpp>
#include <sge/camera/tracking/json/keyframes_to_json.hpp>
#include <sge/input/event_base.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/log/default_parameters.hpp>
#include <sge/log/location.hpp>
#include <sge/parse/json/array_or_object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/output/to_file.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::camera::tracking::json::key_press_exporter::key_press_exporter(
    fcppt::log::context_reference const _log_context,
    sge::camera::base const &_camera,
    std::filesystem::path &&_target_path,
    sge::camera::update_duration const &_duration,
    keyframe_keypress const &_keyframe_keypress,
    export_keypress const &_export_keypress)
    : log_{_log_context, sge::log::location(), sge::log::default_parameters(sge::camera::impl::log_name())},
      camera_{_camera},
      target_path_{std::move(_target_path)},
      duration_{_duration},
      keyframe_keypress_{_keyframe_keypress},
      export_keypress_{_export_keypress},
      keyframes_{}
{
}

FCPPT_PP_POP_WARNING

sge::camera::tracking::json::key_press_exporter::~key_press_exporter() = default;

void sge::camera::tracking::json::key_press_exporter::process_event(
    sge::input::event_base const &_event)
{
  fcppt::optional::maybe_void(
      fcppt::cast::dynamic<sge::input::keyboard::event::key const>(_event),
      [this](fcppt::reference<sge::input::keyboard::event::key const> const _key_event)
      { this->key_event(_key_event.get()); });
}

void sge::camera::tracking::json::key_press_exporter::key_event(
    sge::input::keyboard::event::key const &_key_event)
{
  if (!_key_event.pressed())
  {
    return;
  }

  if (_key_event.get().code() == keyframe_keypress_.get())
  {
    FCPPT_LOG_INFO(log_, fcppt::log::out << FCPPT_TEXT("Storing keyframe..."))

    keyframes_.push_back(sge::camera::tracking::keyframe(duration_, camera_.coordinate_system()));

    FCPPT_LOG_INFO(log_, fcppt::log::out << FCPPT_TEXT("Done!"))
  }
  else if (_key_event.get().code() == export_keypress_.get())
  {
    FCPPT_LOG_INFO(
        log_,
        fcppt::log::out << FCPPT_TEXT("Storing keyframe file ") << target_path_
                        << FCPPT_TEXT("..."))

    if (!sge::parse::json::output::to_file(
            target_path_,
            sge::parse::json::start(sge::parse::json::array_or_object(
                sge::camera::tracking::json::keyframes_to_json(keyframes_)))))
    {
      throw sge::camera::exception(
          FCPPT_TEXT("Couldn't write to file \"") +
          fcppt::filesystem::path_to_string(target_path_) + FCPPT_TEXT('"'));
    }

    FCPPT_LOG_INFO(log_, fcppt::log::out << FCPPT_TEXT("Done!"))
  }
}
