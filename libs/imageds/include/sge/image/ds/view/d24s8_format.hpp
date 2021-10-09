//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_DS_VIEW_D24S8_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_DS_VIEW_D24S8_FORMAT_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <sge/image/ds/d24s8_format.hpp>
#include <sge/image/view/basic_format.hpp>

namespace sge::image::ds::view
{

template <sge::image::size_type Dim>
using d24s8_format = sge::image::view::basic_format<Dim, sge::image::ds::d24s8_format>;

}

#endif
