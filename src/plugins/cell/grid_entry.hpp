#ifndef SGE_CELL_GRID_ENTRY_HPP_INCLUDED
#define SGE_CELL_GRID_ENTRY_HPP_INCLUDED

#include "intrusive_backlink_list.hpp"

namespace sge
{
namespace cell
{

class grid_entry {
public:
	grid_entry();

	grid_entry(
		grid_entry const &);
	grid_entry &
	operator=(
		grid_entry const &);

	intrusive_backlink_list &
	entries();
private:
	intrusive_backlink_list entries_;
};

}
}

#endif
