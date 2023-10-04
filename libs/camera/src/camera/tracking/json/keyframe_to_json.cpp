//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/matrix_conversion/world.hpp>
#include <sge/camera/tracking/keyframe.hpp>
#include <sge/camera/tracking/json/keyframe_to_json.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/float_type.hpp>
#include <sge/parse/json/make_value.hpp>
#include <sge/parse/json/member.hpp>
#include <sge/parse/json/member_map.hpp>
#include <sge/parse/json/object.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/make_recursive.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

sge::parse::json::object
sge::camera::tracking::json::keyframe_to_json(sge::camera::tracking::keyframe const &_keyframe)
{
  sge::parse::json::object result{sge::parse::json::member_map{sge::parse::json::member{
      std::string{"duration"},
      sge::parse::json::make_value(
          static_cast<sge::parse::json::float_type>(_keyframe.duration().count()))}}};

  sge::renderer::matrix4 const matrix(
      sge::camera::matrix_conversion::world(_keyframe.coordinate_system()));

  sge::parse::json::array result_matrix{sge::parse::json::element_vector{}};

  // TODO(philipp): map?
  for (sge::renderer::matrix4::size_type i = 0; i < sge::renderer::matrix4::rows(); ++i)
  {
    sge::parse::json::array result_matrix_row{sge::parse::json::element_vector{}};

    for (sge::renderer::matrix4::size_type j = 0; j < sge::renderer::matrix4::columns(); ++j)
    {
      result_matrix_row.elements.push_back(fcppt::make_recursive(sge::parse::json::make_value(
          static_cast<sge::parse::json::float_type>(matrix.get_unsafe(i).get_unsafe(j)))));
    }

    result_matrix.elements.push_back(
        fcppt::make_recursive(sge::parse::json::make_value(result_matrix_row)));
  }

  result.members.insert(
      sge::parse::json::member(std::string{"matrix"}, sge::parse::json::make_value(result_matrix)));

  return result;
}
