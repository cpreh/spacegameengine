//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_DIM_FWD_HPP_INCLUDED
#define SGE_IMAGE_DIM_FWD_HPP_INCLUDED

#include <sge/image/basic_dim_fwd.hpp>
#include <sge/image/traits/image/dimension.hpp>

namespace sge::image
{

template <typename Tag>
using dim = sge::image::basic_dim<sge::image::traits::image::dimension<Tag>::value>;

}

#endif
