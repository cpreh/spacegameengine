#ifndef SGE_CEGUI_VF_FORMAT_HPP_INCLUDED
#define SGE_CEGUI_VF_FORMAT_HPP_INCLUDED

#include <sge/cegui/vf/part.hpp>
#include <sge/renderer/vf/format.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace cegui
{
namespace vf
{
typedef 
sge::renderer::vf::format
<
	boost::mpl::vector1
	<
		part
	>
> 
format;
}
}
}

#endif
