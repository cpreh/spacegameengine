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


#include <sge/camera/tracking/json/keyframe_from_json.hpp>
#include <sge/camera/tracking/json/keyframes_from_json.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/get.hpp>
#include <sge/parse/json/object.hpp>


sge::camera::tracking::keyframe_sequence const
sge::camera::tracking::json::keyframes_from_json(
	sge::parse::json::array const &_array)
{
	sge::camera::tracking::keyframe_sequence result;

	for(
		sge::parse::json::element_vector::const_iterator it =
			_array.elements.begin();
		it != _array.elements.end();
		++it)
		result.push_back(
			sge::camera::tracking::json::keyframe_from_json(
				sge::parse::json::get<sge::parse::json::object const>(
					*it)));

	return
		result;
}
