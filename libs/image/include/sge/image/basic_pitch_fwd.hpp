//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_BASIC_PITCH_FWD_HPP_INCLUDED
#define SGE_IMAGE_BASIC_PITCH_FWD_HPP_INCLUDED

#include <sge/image/difference_type.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/dim/static_fwd.hpp>

namespace sge::image
{

template <fcppt::math::size_type Dim>
using basic_pitch = fcppt::math::dim::static_<sge::image::difference_type, Dim - 1U>;

}

#endif
