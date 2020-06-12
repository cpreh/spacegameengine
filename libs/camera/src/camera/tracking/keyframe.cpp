//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/update_duration.hpp>
#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/tracking/keyframe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::camera::tracking::keyframe::keyframe(
	sge::camera::update_duration const &_duration,
	sge::camera::coordinate_system::object _coordinate_system
)
:
	duration_(
		_duration
	),
	coordinate_system_(
		std::move(
			_coordinate_system
		)
	)
{
}

sge::camera::update_duration const &
sge::camera::tracking::keyframe::duration() const
{
	return
		duration_;
}

sge::camera::coordinate_system::object const &
sge::camera::tracking::keyframe::coordinate_system() const
{
	return
		coordinate_system_;
}
