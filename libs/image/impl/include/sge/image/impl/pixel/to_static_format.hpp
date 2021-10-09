//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_IMPL_PIXEL_TO_STATIC_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_IMPL_PIXEL_TO_STATIC_FORMAT_HPP_INCLUDED

#include <sge/image/impl/format_key.hpp>
#include <sge/image/impl/traits/pixel/format_map.hpp>
#include <fcppt/mpl/map/at.hpp>

namespace sge::image::impl::pixel
{

template <typename Tag, typename FormatEnum>
using to_static_format = fcppt::mpl::map::at<
    sge::image::impl::traits::pixel::format_map<Tag>,
    sge::image::impl::format_key<typename FormatEnum::value_type, FormatEnum::value>>;

}

#endif
