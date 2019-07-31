//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_SCENE_MATERIAL_FROM_OBJ_MATERIAL_HPP_INCLUDED
#define SGE_SCENIC_SCENE_MATERIAL_FROM_OBJ_MATERIAL_HPP_INCLUDED

#include <sge/model/obj/material/object.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/scene/material/object.hpp>


namespace sge
{
namespace scenic
{
namespace scene
{
namespace material
{
SGE_SCENIC_DETAIL_SYMBOL
sge::scenic::scene::material::object
from_obj_material(
	sge::model::obj::material::object const &);
}
}
}
}

#endif
