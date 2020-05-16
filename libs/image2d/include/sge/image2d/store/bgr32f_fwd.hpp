//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_STORE_BGR32F_FWD_HPP_INCLUDED
#define SGE_IMAGE2D_STORE_BGR32F_FWD_HPP_INCLUDED

#include <sge/image/store/basic_fwd.hpp>
#include <sge/image2d/bgr32f_format.hpp>


namespace sge
{
namespace image2d
{
namespace store
{

using
bgr32f
=
sge::image::store::basic<
	sge::image2d::bgr32f_format
>;

}
}
}

#endif
