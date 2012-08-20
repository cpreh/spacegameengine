#ifndef SGE_POSTPROCESSING_VF_FORMAT_PART_HPP_INCLUDED
#define SGE_POSTPROCESSING_VF_FORMAT_PART_HPP_INCLUDED

#include <sge/postprocessing/vf/position.hpp>
#include <sge/postprocessing/vf/texcoord.hpp>
#include <sge/renderer/vf/part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace postprocessing
{
namespace vf
{
typedef
sge::renderer::vf::part
<
	boost::mpl::vector2
	<
		sge::postprocessing::vf::position,
		sge::postprocessing::vf::texcoord
	>
>
format_part;
}
}
}

#endif

