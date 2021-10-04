//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_ANY_VIEW_FWD_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ANY_VIEW_FWD_HPP_INCLUDED

#include <sge/renderer/index/nonconst_tag.hpp>
#include <sge/renderer/index/any/basic_view_fwd.hpp>


namespace sge::renderer::index::any
{

using
view
=
sge::renderer::index::any::basic_view<
	sge::renderer::index::nonconst_tag
>;

}

#endif
