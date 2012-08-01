#ifndef SGE_MODEL_OBJ_MATERIAL_MAP_HPP_INCLUDED
#define SGE_MODEL_OBJ_MATERIAL_MAP_HPP_INCLUDED

#include <sge/model/obj/identifier.hpp>
#include <sge/model/obj/material.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace obj
{
typedef
std::map
<
	sge::model::obj::identifier,
	sge::model::obj::material
>
material_map;
}
}
}

#endif
