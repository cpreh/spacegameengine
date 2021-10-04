//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_GRID_RECT_HPP_INCLUDED
#define SGE_SCENIC_GRID_RECT_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/math/box/object_fwd.hpp>


namespace sge::scenic::grid
{

using
rect
=
fcppt::math::box::object<
	sge::renderer::scalar,
	2
>;

}

#endif
