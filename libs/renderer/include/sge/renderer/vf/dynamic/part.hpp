//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_PART_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_PART_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/element_list.hpp>
#include <sge/renderer/vf/dynamic/offset_list.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_list.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class part
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	part(
		sge::renderer::vf::dynamic::element_list const &,
		sge::renderer::vf::dynamic::offset_list const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::ordered_element_list const &
	elements() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::vf::dynamic::stride
	stride() const;
private:
	sge::renderer::vf::dynamic::ordered_element_list elements_;

	sge::renderer::vf::dynamic::stride stride_;
};

}
}
}
}

#endif
