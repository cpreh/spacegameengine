//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_TRACKING_JSON_KEYFRAMES_FROM_JSON_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_JSON_KEYFRAMES_FROM_JSON_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/tracking/keyframe_sequence.hpp>
#include <sge/parse/json/array_fwd.hpp>

namespace sge::camera::tracking::json
{

SGE_CAMERA_DETAIL_SYMBOL
sge::camera::tracking::keyframe_sequence keyframes_from_json(sge::parse::json::array const &);

}

#endif
