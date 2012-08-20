#ifndef SGE_POSTPROCESSING_VF_POSITION_HPP_INCLUDED
#define SGE_POSTPROCESSING_VF_POSITION_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vf/pos.hpp>

namespace sge
{
namespace postprocessing
{
namespace vf
{
typedef
sge::renderer::vf::pos
<
	sge::renderer::scalar,
	2
>
position;
}
}
}

#endif

