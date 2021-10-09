//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SCENIC_GRID_ORIENTATION_HPP_INCLUDED
#define SGE_SCENIC_GRID_ORIENTATION_HPP_INCLUDED

#include <sge/scenic/grid/orientation_fwd.hpp>

namespace sge::scenic::grid
{

enum class orientation
{
  xz,
  xy,
  yz,
  fcppt_maximum = yz
};

}

#endif
