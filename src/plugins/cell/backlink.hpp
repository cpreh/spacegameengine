#ifndef SGE_CELL_BACKLINK_HPP_INCLUDED
#define SGE_CELL_BACKLINK_HPP_INCLUDED

#include "circle_list.hpp"

namespace sge
{
namespace cell
{

class grid_entry;

class backlink {
public:
	backlink(
		grid_entry &,
		circle_list::iterator);
	
	grid_entry &entry();
	void unlink();
private:
	grid_entry &entry_;
	circle_list::iterator it;
};

}
}

#endif
