//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/spherical/coordinate_system/homogenous.hpp>
#include <sge/camera/spherical/coordinate_system/object.hpp>


sge::camera::spherical::coordinate_system::object
sge::camera::spherical::coordinate_system::homogenous(
	sge::renderer::scalar const v)
{
	return
		sge::camera::spherical::coordinate_system::object(
			spherical::coordinate_system::azimuth(
				v),
			spherical::coordinate_system::inclination(
				v),
			spherical::coordinate_system::radius(
				v));
}
