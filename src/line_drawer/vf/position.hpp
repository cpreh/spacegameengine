#ifndef SGE_LINE_DRAWER_VF_POSITION_HPP_INCLUDED
#define SGE_LINE_DRAWER_VF_POSITION_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vf/pos.hpp>

namespace sge
{
namespace line_drawer
{
namespace vf
{
typedef 
sge::renderer::vf::pos
<
	sge::renderer::scalar,
	3
> 
position;
}
}
}

#endif
