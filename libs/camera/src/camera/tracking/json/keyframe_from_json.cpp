//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/update_duration.hpp>
#include <sge/camera/matrix_conversion/world_matrix_to_coordinate_system.hpp>
#include <sge/camera/tracking/keyframe.hpp>
#include <sge/camera/tracking/json/keyframe_from_json.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/parse/json/find_and_convert_member.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/parse/json/path.hpp>
#include <sge/renderer/matrix4.hpp>

sge::camera::tracking::keyframe
sge::camera::tracking::json::keyframe_from_json(sge::parse::json::object const &_object)
{
  return sge::camera::tracking::keyframe(
      sge::camera::update_duration(
          sge::parse::json::find_and_convert_member<sge::camera::update_duration::rep>(
              _object, sge::parse::json::path{sge::charconv::utf8_string{"duration"}})),
      sge::camera::matrix_conversion::world_matrix_to_coordinate_system(
          sge::parse::json::find_and_convert_member<sge::renderer::matrix4>(
              _object, sge::parse::json::path(sge::charconv::utf8_string{"matrix"}))));
}
