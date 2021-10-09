//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_VIEW_TO_WRAPPED_TYPE_FWD_HPP_INCLUDED
#define SGE_IMAGE_VIEW_TO_WRAPPED_TYPE_FWD_HPP_INCLUDED

#include <sge/image/view/mizuiro_type_fwd.hpp>

namespace sge::image::view
{

template <typename View>
using to_wrapped_type =
    sge::image::view::mizuiro_type<typename View::format, typename View::constness>;

}

#endif
