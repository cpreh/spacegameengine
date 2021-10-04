//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGEDS2D_STORE_D16_FWD_HPP_INCLUDED
#define SGE_IMAGEDS2D_STORE_D16_FWD_HPP_INCLUDED

#include <sge/image/store/basic_fwd.hpp>
#include <sge/imageds2d/d16_format.hpp>


namespace sge::imageds2d::store
{

using
d16
=
sge::image::store::basic<
	sge::imageds2d::d16_format
>;

}

#endif
