//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/camera/tracking/keyframe.hpp>
#include <sge/camera/tracking/keyframe_sequence.hpp>
#include <sge/camera/tracking/json/keyframe_to_json.hpp>
#include <sge/camera/tracking/json/keyframes_to_json.hpp>
#include <sge/parse/json/array.hpp>
#include <sge/parse/json/element_vector.hpp>
#include <sge/parse/json/make_value.hpp>
#include <fcppt/make_recursive.hpp>
#include <fcppt/algorithm/map.hpp>

sge::parse::json::array sge::camera::tracking::json::keyframes_to_json(
    sge::camera::tracking::keyframe_sequence const &_keyframes)
{
  return sge::parse::json::array{fcppt::algorithm::map<sge::parse::json::element_vector>(
      _keyframes,
      [](sge::camera::tracking::keyframe const &_keyframe)
      {
        return fcppt::make_recursive(
            sge::parse::json::make_value(sge::camera::tracking::json::keyframe_to_json(_keyframe)));
      })};
}
