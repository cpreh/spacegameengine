#ifndef SGE_SCENIC_SCENE_MATERIAL_FROM_OBJ_MATERIAL_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MATERIAL_FROM_OBJ_MATERIAL_HPP_INCLUDED

#include <sge/model/obj/material/object.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/scenic/scene/material/object.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{
namespace material
{
SGE_SCENIC_SYMBOL
sge::scenic::scene::material::object const
from_obj_material(
	sge::model::obj::material::object const &);
}
}
}
}

#endif
