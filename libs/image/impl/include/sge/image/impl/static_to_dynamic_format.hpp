//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_STATIC_TO_DYNAMIC_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_IMPL_STATIC_TO_DYNAMIC_FORMAT_HPP_INCLUDED

#include <sge/image/impl/traits/pixel/format_map.hpp>
#include <fcppt/mpl/map/at.hpp>
#include <fcppt/mpl/map/flip.hpp>

namespace sge::image::impl
{

template <typename ColorTag, typename StaticFormat>
using static_to_dynamic_format = fcppt::mpl::map::
    at<fcppt::mpl::map::flip<sge::image::impl::traits::pixel::format_map<ColorTag>>, StaticFormat>;

}

#endif
