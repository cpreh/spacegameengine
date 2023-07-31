//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/base.hpp>
#include <sge/camera/exception.hpp>
#include <sge/camera/tracking/json/interval_exporter.hpp>
#include <sge/camera/tracking/json/keyframes_to_json.hpp>
#include <sge/parse/json/array_or_object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/value.hpp>
#include <sge/parse/json/output/to_file.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::camera::tracking::json::interval_exporter::interval_exporter(
    fcppt::reference<sge::camera::base const> const _camera,
    sge::camera::update_duration const &_update_duration,
    std::filesystem::path &&_export_file_path)
    : camera_(_camera),
      update_timer_(sge::timer::parameters<sge::timer::clocks::standard>(
          std::chrono::duration_cast<sge::timer::clocks::standard::duration>(_update_duration))),
      export_file_path_(std::move(_export_file_path)),
      keyframes_()
{
}

void sge::camera::tracking::json::interval_exporter::update()
{
  if (!sge::timer::reset_when_expired(fcppt::make_ref(update_timer_)))
  {
    return;
  }

  // NOLINTNEXTLINE(hicpp-use-emplace,modernize-use-emplace)
  keyframes_.push_back(sge::camera::tracking::keyframe(
      std::chrono::duration_cast<sge::camera::update_duration>(update_timer_.interval()),
      camera_.get().coordinate_system()));
}

sge::camera::tracking::json::interval_exporter::~interval_exporter() noexcept(false)
{
  if (!sge::parse::json::output::to_file(
          export_file_path_,
          sge::parse::json::start(sge::parse::json::array_or_object(
              sge::camera::tracking::json::keyframes_to_json(keyframes_)))))
  {
    throw sge::camera::exception(
        FCPPT_TEXT("Couldn't write to file \"") +
        fcppt::filesystem::path_to_string(export_file_path_) + FCPPT_TEXT('"'));
  }
}
