//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_PIXEL_CONVERT_HPP_INCLUDED
#define SGE_IMAGE_PIXEL_CONVERT_HPP_INCLUDED

#include <sge/image/enable_if_has_format.hpp>
#include <sge/image/detail/instantiate/symbol.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <sge/image/pixel/object_fwd.hpp>

namespace sge::image::pixel
{

template <typename Tag, typename Format>
SGE_IMAGE_DETAIL_INSTANTIATE_SYMBOL
    sge::image::enable_if_has_format<Tag, Format, sge::image::pixel::mizuiro_type<Format>>
    convert(sge::image::pixel::object<Tag> const &);

}

#endif
