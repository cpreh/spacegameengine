//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE3D_STORE_A8_FWD_HPP_INCLUDED
#define SGE_IMAGE3D_STORE_A8_FWD_HPP_INCLUDED

#include <sge/image/store/basic_fwd.hpp>
#include <sge/image3d/a8_format.hpp>


namespace sge::image3d::store
{

using
a8
=
sge::image::store::basic<
	sge::image3d::a8_format
>;

}

#endif
