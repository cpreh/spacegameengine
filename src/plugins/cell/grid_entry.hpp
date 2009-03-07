#ifndef SGE_CELL_GRID_ENTRY_HPP_INCLUDED
#define SGE_CELL_GRID_ENTRY_HPP_INCLUDED

#include "circle_list.hpp"
#include <sge/collision/rect.hpp>
#include <sge/collision/time_unit.hpp>

namespace sge
{
namespace cell
{

class grid_entry {
public:
	void update(
		collision::time_unit);
	
	circle_list &
	entries();
private:
	circle_list entries_;
};

}
}

#endif
