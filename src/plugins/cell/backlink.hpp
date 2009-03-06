#ifndef SGE_CELL_BACKLINK_HPP_INCLUDED
#define SGE_CELL_BACKLINK_HPP_INCLUDED

#include "weak_circle_list.hpp"

namespace sge
{
namespace cell
{

class grid_entry;

class backlink {
public:
	backlink(
		grid_entry &,
		weak_circle_list::iterator);
	
	grid_entry &entry() const;
private:
	grid_entry &entry_;
	weak_circle_list::iterator it;
};

}
}

#endif
