//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_OPTIONAL_PROJECTION_MATRIX_FWD_HPP_INCLUDED
#define SGE_CAMERA_OPTIONAL_PROJECTION_MATRIX_FWD_HPP_INCLUDED

#include <sge/camera/projection_matrix_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace camera
{

using
optional_projection_matrix
=
fcppt::optional::object<
	sge::camera::projection_matrix
>;

}
}

#endif

