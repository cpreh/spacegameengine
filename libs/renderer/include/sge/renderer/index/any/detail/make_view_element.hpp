//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_ANY_DETAIL_MAKE_VIEW_ELEMENT_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ANY_DETAIL_MAKE_VIEW_ELEMENT_HPP_INCLUDED

#include <sge/renderer/index/format_fwd.hpp>
#include <sge/renderer/index/view_fwd.hpp>
#include <sge/renderer/index/dynamic/format_element.hpp>

namespace sge::renderer::index::any::detail
{

template <typename Element, typename Constness>
using make_view_element = sge::renderer::index::view<
    sge::renderer::index::format<
        typename sge::renderer::index::dynamic::format_element<Element::value>::type>,
    Constness>;

}

#endif
