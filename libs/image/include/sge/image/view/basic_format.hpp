//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_VIEW_BASIC_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_VIEW_BASIC_FORMAT_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <mizuiro/image/dimension_impl.hpp>
#include <mizuiro/image/format/interleaved.hpp>

namespace sge::image::view
{

template <sge::image::size_type Dim, typename ColorFormat>
using basic_format =
    mizuiro::image::format::interleaved<mizuiro::image::dimension<Dim>, ColorFormat>;

}

#endif
