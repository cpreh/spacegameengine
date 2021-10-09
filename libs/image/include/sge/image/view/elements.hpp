//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_VIEW_ELEMENTS_HPP_INCLUDED
#define SGE_IMAGE_VIEW_ELEMENTS_HPP_INCLUDED

#include <sge/image/view/basic_elements.hpp>
#include <mizuiro/nonconst_tag.hpp>

namespace sge::image::view
{

template <typename Tag>
using elements = sge::image::view::basic_elements<Tag, mizuiro::nonconst_tag>;

}

#endif
