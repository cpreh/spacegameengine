#ifndef SGE_CEGUI_VF_COLOR_HPP_INCLUDED
#define SGE_CEGUI_VF_COLOR_HPP_INCLUDED

#include <sge/renderer/vf/color.hpp>
#include <sge/image/color/rgba8_format.hpp>

namespace sge
{
namespace cegui
{
namespace vf
{
typedef 
sge::renderer::vf::color
<
	sge::image::color::rgba8_format
> 
color;
}
}
}

#endif
