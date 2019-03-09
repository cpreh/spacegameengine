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


#include <sge/camera/tracking/keyframe.hpp>
#include <sge/camera/tracking/keyframe_sequence.hpp>
#include <sge/camera/tracking/json/keyframe_to_json.hpp>
#include <sge/camera/tracking/json/keyframes_to_json.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/make_value.hpp>
#include <fcppt/make_recursive.hpp>
#include <fcppt/algorithm/map.hpp>


sge::parse::json::array
sge::camera::tracking::json::keyframes_to_json(
	sge::camera::tracking::keyframe_sequence const &_keyframes
)
{
	return
		sge::parse::json::array{
			fcppt::algorithm::map<
				sge::parse::json::element_vector
			>(
				_keyframes,
				[](
					sge::camera::tracking::keyframe const &_keyframe
				)
				{
					return
						fcppt::make_recursive(
							sge::parse::json::make_value(
								sge::camera::tracking::json::keyframe_to_json(
									_keyframe
								)
							)
						);
				}
			)
		};
}
