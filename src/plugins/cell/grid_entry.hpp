#ifndef SGE_CELL_GRID_ENTRY_HPP_INCLUDED
#define SGE_CELL_GRID_ENTRY_HPP_INCLUDED

#include "circle_list.hpp"
#include <sge/collision/rect.hpp>

namespace sge
{
namespace cell
{

class grid_entry {
public:
	explicit grid_entry(
		collision::rect const &);

	void update(
		time::funit);
	
	collision::rect const &
	rect() const;

	circle_list &
	entries() const;
private:
	collision::rect const rect_;
	circle_list entries_;
};

}
}

#endif
