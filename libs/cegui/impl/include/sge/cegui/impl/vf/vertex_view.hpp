//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_VF_VERTEX_VIEW_HPP_INCLUDED
#define SGE_CEGUI_IMPL_VF_VERTEX_VIEW_HPP_INCLUDED

#include <sge/cegui/impl/vf/part.hpp>
#include <sge/renderer/vf/view.hpp>


namespace sge
{
namespace cegui
{
namespace impl
{
namespace vf
{

typedef
sge::renderer::vf::view<
	sge::cegui::impl::vf::part
>
vertex_view;

}
}
}
}

#endif
