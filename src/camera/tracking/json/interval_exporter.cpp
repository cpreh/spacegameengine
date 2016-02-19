/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/camera/base.hpp>
#include <sge/camera/exception.hpp>
#include <sge/camera/tracking/json/interval_exporter.hpp>
#include <sge/camera/tracking/json/keyframes_to_json.hpp>
#include <sge/parse/json/array_or_object.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/output/to_file.hpp>
#include <sge/timer/parameters.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sge::camera::tracking::json::interval_exporter::interval_exporter(
	sge::camera::base const &_camera,
	sge::camera::update_duration const &_update_duration,
	boost::filesystem::path const &_export_file_path
)
:
	camera_(
		_camera
	),
	update_timer_(
		sge::timer::parameters<
			sge::timer::clocks::standard
		>(
			std::chrono::duration_cast<
				sge::timer::clocks::standard::duration
			>(
				_update_duration
			)
		)
	),
	export_file_path_(
		_export_file_path
	),
	keyframes_()
{
}

void
sge::camera::tracking::json::interval_exporter::update()
{
	if(
		!sge::timer::reset_when_expired(
			update_timer_
		)
	)
		return;

	keyframes_.push_back(
		sge::camera::tracking::keyframe(
			std::chrono::duration_cast<
				sge::camera::update_duration
			>(
				update_timer_.interval()
			),
			camera_.coordinate_system()
		)
	);
}

sge::camera::tracking::json::interval_exporter::~interval_exporter()
noexcept(
	false
)
{
	if(
		!sge::parse::json::output::to_file(
			export_file_path_,
			sge::parse::json::start(
				sge::parse::json::array_or_object(
					sge::camera::tracking::json::keyframes_to_json(
						keyframes_
					)
				)
			)
		)
	)
		throw
			sge::camera::exception(
				FCPPT_TEXT("Couldn't write to file \"")
				+
				fcppt::filesystem::path_to_string(
					export_file_path_
				)
				+
				FCPPT_TEXT('"')
			);
}
