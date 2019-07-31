//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/spherical/coordinate_system/null.hpp>
#include <sge/camera/spherical/coordinate_system/object.hpp>

sge::camera::spherical::coordinate_system::object
sge::camera::spherical::coordinate_system::null()
{
	return
		coordinate_system::object(
			coordinate_system::azimuth(
				0.0f),
			coordinate_system::inclination(
				0.0f),
			coordinate_system::radius(
				0.0f));
}
