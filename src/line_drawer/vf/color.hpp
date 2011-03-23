#ifndef SGE_LINE_DRAWER_VF_COLOR_HPP_INCLUDED
#define SGE_LINE_DRAWER_VF_COLOR_HPP_INCLUDED

#include <sge/line_drawer/color_format.hpp>
#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vf/color.hpp>

namespace sge
{
namespace line_drawer
{
namespace vf
{
typedef 
sge::renderer::vf::color
<
	color_format
> 
color;
}
}
}

#endif
