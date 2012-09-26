#ifndef SGE_SCENIC_SCENE_MATERIAL_SHININESS_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MATERIAL_SHININESS_HPP_INCLUDED

#include <sge/renderer/scalar.hpp>
#include <fcppt/strong_typedef.hpp>

namespace sge
{
namespace scenic
{
namespace scene
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
