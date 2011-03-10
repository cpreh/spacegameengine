#ifndef SGE_CEGUI_VF_TEXCOORD_HPP_INCLUDED
#define SGE_CEGUI_VF_TEXCOORD_HPP_INCLUDED

#include <sge/cegui/unit.hpp>
#include <sge/renderer/vf/texpos.hpp>

namespace sge
{
namespace cegui
{
namespace vf
{
typedef 
sge::renderer::vf::texpos
<
	unit,
	2
> 
texcoord;
}
}
}

#endif
