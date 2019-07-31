//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_TRACKING_KEYFRAME_HPP_INCLUDED
#define SGE_CAMERA_TRACKING_KEYFRAME_HPP_INCLUDED

#include <sge/camera/update_duration.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/detail/symbol.hpp>


namespace sge
{
namespace camera
{
namespace tracking
{
class keyframe
{
public:
	SGE_CAMERA_DETAIL_SYMBOL
	keyframe(
		sge::camera::update_duration const &,
		sge::camera::coordinate_system::object const &);

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::update_duration const &
	duration() const;

	SGE_CAMERA_DETAIL_SYMBOL
	sge::camera::coordinate_system::object const &
	coordinate_system() const;
private:
	sge::camera::update_duration duration_;
	sge::camera::coordinate_system::object coordinate_system_;
};
}
}
}

#endif
