//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_GRID_SPACING_HPP_INCLUDED
#define SGE_SCENIC_GRID_SPACING_HPP_INCLUDED

#include <sge/scenic/grid/dim.hpp>
#include <fcppt/make_strong_typedef.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace scenic
{
namespace grid
{
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::scenic::grid::dim,
	spacing);
}
}
}

#endif
