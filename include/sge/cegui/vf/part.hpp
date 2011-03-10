#ifndef SGE_CEGUI_VF_PART_HPP_INCLUDED
#define SGE_CEGUI_VF_PART_HPP_INCLUDED

#include <sge/cegui/vf/position.hpp>
#include <sge/cegui/vf/texcoord.hpp>
#include <sge/cegui/vf/color.hpp>
#include <sge/renderer/vf/part.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace cegui
{
namespace vf
{
typedef 
sge::renderer::vf::part
<
	boost::mpl::vector3
	<
		position,
		texcoord,
		color
	>
> 
part;
}
}
}

#endif
