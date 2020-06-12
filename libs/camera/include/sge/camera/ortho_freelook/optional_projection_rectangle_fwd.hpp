//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_ORTHO_FREELOOK_OPTIONAL_PROJECTION_RECTANGLE_FWD_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_OPTIONAL_PROJECTION_RECTANGLE_FWD_HPP_INCLUDED

#include <sge/renderer/projection/rect_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace camera
{
namespace ortho_freelook
{

using
optional_projection_rectangle
=
fcppt::optional::object<
	sge::renderer::projection::rect
>;

}
}
}

#endif
