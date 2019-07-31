//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_MATRIX_CONVERSION_WORLD_MATRIX_TO_COORDINATE_SYSTEM_HPP_INCLUDED
#define SGE_CAMERA_MATRIX_CONVERSION_WORLD_MATRIX_TO_COORDINATE_SYSTEM_HPP_INCLUDED

#include <sge/camera/coordinate_system/object.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/renderer/matrix4_fwd.hpp>


namespace sge
{
namespace camera
{
namespace matrix_conversion
{

SGE_CAMERA_DETAIL_SYMBOL
sge::camera::coordinate_system::object
world_matrix_to_coordinate_system(
	sge::renderer::matrix4 const &
);

}
}
}

#endif
