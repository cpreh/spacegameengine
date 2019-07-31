//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_ORDERED_ELEMENT_LIST_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_ORDERED_ELEMENT_LIST_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

typedef std::vector<
	sge::renderer::vf::dynamic::ordered_element
> ordered_element_list;

}
}
}
}

#endif
