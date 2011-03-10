#ifndef SGE_CEGUI_VF_POSITION_HPP_INCLUDED
#define SGE_CEGUI_VF_POSITION_HPP_INCLUDED

#include <sge/renderer/vf/pos.hpp>
#include <sge/cegui/unit.hpp>

namespace sge
{
namespace cegui
{
namespace vf
{
// I don't really know why they're using three-dimensional
// coordinates, I just copy & pasted that part.
typedef 
sge::renderer::vf::pos
<
	unit,
	3
> 
position;
}
}
}

#endif
