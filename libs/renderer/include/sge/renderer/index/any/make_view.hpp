//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_ANY_MAKE_VIEW_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ANY_MAKE_VIEW_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/index/any/view_fwd.hpp>
#include <sge/renderer/index/dynamic/view_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace index
{
namespace any
{

SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::index::any::view
make_view(
	sge::renderer::index::dynamic::view const &
);

}
}
}
}

#endif
