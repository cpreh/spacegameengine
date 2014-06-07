/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/exception.hpp>
#include <sge/camera/base.hpp>
#include <sge/camera/tracking/json/key_press_exporter.hpp>
#include <sge/camera/tracking/json/keyframes_to_json.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/key_event.hpp>
#include <sge/parse/json/start.hpp>
#include <sge/parse/json/output/to_file.hpp>
#include <sge/src/camera/logger.hpp>
#include <fcppt/text.hpp>
#include <fcppt/filesystem/path_to_string.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::camera::tracking::json::key_press_exporter::key_press_exporter(
	sge::camera::base const &_camera,
	boost::filesystem::path const &_target_path,
	sge::camera::update_duration const &_duration,
	sge::input::keyboard::device &_keyboard,
	keyframe_keypress const &_keyframe_keypress,
	export_keypress const &_export_keypress)
:
	camera_(
		_camera),
	target_path_(
		_target_path),
	duration_(
		_duration),
	keyframe_keypress_(
		_keyframe_keypress),
	export_keypress_(
		_export_keypress),
	key_press_connection_(
		_keyboard.key_callback(
			std::bind(
				&key_press_exporter::key_callback,
				this,
				std::placeholders::_1))),
	keyframes_()
{
}

FCPPT_PP_POP_WARNING

sge::camera::tracking::json::key_press_exporter::~key_press_exporter()
{
}

void
sge::camera::tracking::json::key_press_exporter::key_callback(
	sge::input::keyboard::key_event const &_key_event)
{
	if(!_key_event.pressed())
		return;

	if(_key_event.key_code() == keyframe_keypress_.get())
	{
		FCPPT_LOG_INFO(
			sge::camera::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Storing keyframe..."));

		keyframes_.push_back(
			sge::camera::tracking::keyframe(
				duration_,
				camera_.coordinate_system()));
		FCPPT_LOG_INFO(
			sge::camera::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Done!"));
	}
	else if(_key_event.key_code() == export_keypress_.get())
	{
		FCPPT_LOG_INFO(
			sge::camera::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Storing keyframe file ")
				<< target_path_
				<< FCPPT_TEXT("..."));
		if(
			!sge::parse::json::output::to_file(
				target_path_,
				sge::parse::json::start(
					sge::parse::json::start_variant(
						sge::camera::tracking::json::keyframes_to_json(
							keyframes_)))))
			throw
				sge::exception(
					FCPPT_TEXT("Couldn't write to file \"")+
					fcppt::filesystem::path_to_string(
						target_path_)+
					FCPPT_TEXT("\""));
		FCPPT_LOG_INFO(
			sge::camera::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Done!"));
	}
}
