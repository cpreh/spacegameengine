#ifndef SGE_CELL_FIELD_TYPE_HPP_INCLUDED
#define SGE_CELL_FIELD_TYPE_HPP_INCLUDED

#include <sge/container/field_fwd.hpp>

namespace sge
{
namespace cell
{

class grid_entry;

typedef container::field<
	grid_entry
> field_type;

}
}

#endif
