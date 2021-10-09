//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_DYNAMIC_MAKE_CONST_VIEW_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DYNAMIC_MAKE_CONST_VIEW_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/dynamic/const_view_fwd.hpp>
#include <sge/renderer/index/dynamic/view_fwd.hpp>

namespace sge::renderer::index::dynamic
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::index::dynamic::const_view
make_const_view(sge::renderer::index::dynamic::view const &);

}

#endif
