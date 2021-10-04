//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE3D_ALGORITHM_PRINT_HPP_INCLUDED
#define SGE_IMAGE3D_ALGORITHM_PRINT_HPP_INCLUDED

#include <sge/image3d/detail/symbol.hpp>
#include <sge/image3d/view/const_object_fwd.hpp>
#include <fcppt/io/ostream_fwd.hpp>


namespace sge::image3d::algorithm
{

SGE_IMAGE3D_DETAIL_SYMBOL
void
print(
	fcppt::io::ostream &,
	sge::image3d::view::const_object const &
);

}

#endif
