//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_MODEL_OBJ_MATERIAL_MAP_HPP_INCLUDED
#define SGE_MODEL_OBJ_MATERIAL_MAP_HPP_INCLUDED

#include <sge/model/obj/identifier.hpp>
#include <sge/model/obj/material/object.hpp>
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
	sge::model::obj::material::object
>
material_map;
}
}
}

#endif
