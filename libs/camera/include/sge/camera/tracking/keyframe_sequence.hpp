//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CAMERA_TRACKING_KEYFRAME_SEQUENCE_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_KEYFRAME_SEQUENCE_HPP_INCLUDED

#include <sge/camera/tracking/keyframe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace sge::camera::tracking
{

using keyframe_sequence = std::vector<sge::camera::tracking::keyframe>;

}

#endif
