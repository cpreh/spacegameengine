#ifndef SGE_CELL_INTRUSIVE_BACKLINK_LIST_HPP_INCLUDED
#define SGE_CELL_INTRUSIVE_BACKLINK_LIST_HPP_INCLUDED

#include "backlink.hpp"
#include <boost/intrusive/list.hpp>

namespace sge
{
namespace cell
{

typedef boost::intrusive::list<
	backlink,
	boost::intrusive::constant_time_size<
		false
	>
> intrusive_backlink_list;

}
}

#endif
