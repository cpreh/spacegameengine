//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_VIEW_MIZUIRO_TYPE_FWD_HPP_INCLUDED
#define SGE_IMAGE_VIEW_MIZUIRO_TYPE_FWD_HPP_INCLUDED

#include <sge/image/view/mizuiro_access.hpp>
#include <sge/image/view/mizuiro_traits.hpp> // IWYU pragma: keep
#include <mizuiro/image/view_fwd.hpp>

namespace sge::image::view
{

template <typename Format, typename Constness>
using mizuiro_type = mizuiro::image::view<sge::image::view::mizuiro_access, Format, Constness>;

}

#endif
