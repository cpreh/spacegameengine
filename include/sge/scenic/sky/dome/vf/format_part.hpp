#ifndef SGE_SCENIC_SKY_DOME_VF_FORMAT_PART_HPP_INCLUDED
#define SGE_SCENIC_SKY_DOME_VF_FORMAT_PART_HPP_INCLUDED

#include <sge/renderer/vf/part.hpp>
#include <sge/scenic/sky/dome/vf/position.hpp>
#include <sge/scenic/sky/dome/vf/texcoord.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace scenic
{
namespace sky
{
namespace dome
{
namespace vf
{
typedef
sge::renderer::vf::part
<
	boost::mpl::vector2
	<
		sge::scenic::sky::dome::vf::position,
		sge::scenic::sky::dome::vf::texcoord
	>
>
format_part;
}
}
}
}
}

#endif

