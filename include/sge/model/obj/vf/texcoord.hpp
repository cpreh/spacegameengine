#ifndef SGE_MODEL_OBJ_VF_TEXCOORD_HPP_INCLUDED
#define SGE_MODEL_OBJ_VF_TEXCOORD_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/texpos.hpp>


namespace sge
{
namespace model
{
namespace obj
{
namespace vf
{
typedef
sge::renderer::vf::texpos
<
	sge::renderer::scalar,
	2,
	sge::renderer::vf::index<0u>
>
texcoord;
}
}
}
}

#endif

