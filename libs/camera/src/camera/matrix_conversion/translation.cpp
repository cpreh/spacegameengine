//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/matrix_conversion/translation.hpp>
#include <sge/renderer/matrix4.hpp>
#include <fcppt/math/matrix/translation.hpp>


sge::renderer::matrix4
sge::camera::matrix_conversion::translation(
	sge::camera::coordinate_system::object const &_coordinate_system
)
{
	return
		fcppt::math::matrix::translation(
			_coordinate_system.position().get()
		);
}
