#ifndef SGE_MODEL_OBJ_MATERIAL_TO_INDEX_BUFFER_RANGE_HPP_INCLUDED
#define SGE_MODEL_OBJ_MATERIAL_TO_INDEX_BUFFER_RANGE_HPP_INCLUDED

#include <sge/model/obj/identifier.hpp>
#include <sge/model/obj/index_buffer_range.hpp>
#include <fcppt/config/external_begin.hpp>
#include <map>
#include <string>
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
	sge::model::obj::index_buffer_range
>
material_to_index_buffer_range;
}
}
}

#endif
