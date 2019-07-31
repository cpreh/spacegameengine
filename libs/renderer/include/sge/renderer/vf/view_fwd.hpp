//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_VIEW_FWD_HPP_INCLUDED
#define SGE_RENDERER_VF_VIEW_FWD_HPP_INCLUDED

#include <sge/renderer/vf/nonconst_tag.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename VertexFormat,
	typename Constness = sge::renderer::vf::nonconst_tag
>
class view;

}
}
}

#endif
