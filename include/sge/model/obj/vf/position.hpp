#ifndef SGE_MODEL_OBJ_VF_POSITION_HPP_INCLUDED
#define SGE_MODEL_OBJ_VF_POSITION_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vf/pos.hpp>

namespace sge
{
namespace model
{
namespace obj
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
}

#endif

