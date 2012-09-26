#ifndef SGE_MODEL_OBJ_MATERIAL_SHININESS_HPP_INCLUDED
#define SGE_MODEL_OBJ_MATERIAL_SHININESS_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace model
{
namespace obj
{
namespace material
{
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::renderer::scalar,
	shininess);
}
}
}
}

#endif
