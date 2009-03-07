#ifndef SGE_CELL_BACKLINK_HPP_INCLUDED
#define SGE_CELL_BACKLINK_HPP_INCLUDED

#include "circle_list.hpp"
#include <boost/intrusive/list_hook.hpp>

namespace sge
{
namespace cell
{

class grid_entry;

class backlink
:
public boost::intrusive::list_base_hook<
	boost::intrusive::link_mode<
		boost::intrusive::auto_unlink
	>
> {
public:
	backlink(
		grid_entry &,
		cell::circle &);
	
	grid_entry &entry();
	cell::circle &circle();
private:
	grid_entry *entry_;
	cell::circle *circle_;
};

}
}

#endif
