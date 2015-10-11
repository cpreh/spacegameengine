/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/camera/matrix_conversion/world_matrix_to_coordinate_system.hpp>
#include <sge/camera/tracking/keyframe.hpp>
#include <sge/camera/tracking/json/keyframe_from_json.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <fcppt/text.hpp>


sge::camera::tracking::keyframe
sge::camera::tracking::json::keyframe_from_json(
	sge::parse::json::object const &_object
)
{
	return
		sge::camera::tracking::keyframe(
			sge::camera::update_duration(
				sge::parse::json::find_and_convert_member<
					sge::camera::update_duration::rep
				>(
					_object,
					sge::parse::json::path(
						fcppt::string(
							FCPPT_TEXT("duration")
						)
					)
				)
			),
			sge::camera::matrix_conversion::world_matrix_to_coordinate_system(
				sge::parse::json::find_and_convert_member<
					sge::renderer::matrix4
				>(
					_object,
					sge::parse::json::path(
						fcppt::string(
							FCPPT_TEXT("matrix")
						)
					)
				)
			)
		);
}
