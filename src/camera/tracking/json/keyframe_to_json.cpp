/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/tracking/keyframe.hpp>
#include <sge/camera/tracking/json/keyframe_to_json.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/matrix/object_impl.hpp>


sge::parse::json::object const
sge::camera::tracking::json::keyframe_to_json(
	sge::camera::tracking::keyframe const &_keyframe)
{
	sge::parse::json::object result;
	result.members.insert(
		sge::parse::json::member_map::value_type(
			fcppt::string(
				FCPPT_TEXT("duration")),
			sge::parse::json::value(
				static_cast<sge::parse::json::float_type>(
					_keyframe.duration().count()))));

	sge::renderer::matrix4 const matrix(
		sge::camera::matrix_conversion::world(
			_keyframe.coordinate_system()));

	sge::parse::json::array result_matrix;

	for(sge::renderer::matrix4::size_type i = 0; i < matrix.rows(); ++i)
	{
		sge::parse::json::array result_matrix_row;
		for(sge::renderer::matrix4::size_type j = 0; j < matrix.columns(); ++j)
			result_matrix_row.elements.push_back(
				sge::parse::json::value(
					static_cast<sge::parse::json::float_type>(
						matrix[i][j])));
		result_matrix.elements.push_back(
			sge::parse::json::value(
				result_matrix_row));
	}

	result.members.insert(
		sge::parse::json::member_map::value_type(
			fcppt::string(
				FCPPT_TEXT("matrix")),
			result_matrix));

	return
		result;
}
