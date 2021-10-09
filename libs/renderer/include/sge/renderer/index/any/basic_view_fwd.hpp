//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_ANY_BASIC_VIEW_FWD_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ANY_BASIC_VIEW_FWD_HPP_INCLUDED

#include <sge/renderer/index/any/detail/variant_types.hpp>
#include <fcppt/variant/from_list_fwd.hpp>

namespace sge::renderer::index::any
{

template <typename Constness>
using basic_view =
    fcppt::variant::from_list<sge::renderer::index::any::detail::variant_types<Constness>>;

}

#endif
