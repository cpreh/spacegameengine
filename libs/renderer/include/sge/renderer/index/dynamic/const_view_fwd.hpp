//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_DYNAMIC_CONST_VIEW_FWD_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DYNAMIC_CONST_VIEW_FWD_HPP_INCLUDED

#include <sge/renderer/index/dynamic/basic_view_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace index
{
namespace dynamic
{

using
const_view
=
sge::renderer::index::dynamic::basic_view<
	true
>;

}
}
}
}

#endif
