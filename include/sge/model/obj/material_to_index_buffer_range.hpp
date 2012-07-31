#ifndef SGE_MODEL_OBJ_MATERIAL_TO_INDEX_BUFFER_RANGE_HPP_INCLUDED
#define SGE_MODEL_OBJ_MATERIAL_TO_INDEX_BUFFER_RANGE_HPP_INCLUDED

#include <sge/model/obj/index_buffer_range.hpp>
#include <string>
#include <map>

namespace sge
{
namespace model
{
namespace obj
{
typedef
std::map
<
	std::string,
	sge::model::obj::index_buffer_range
>
material_to_index_buffer_range;
}
}
}

#endif
