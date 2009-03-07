#ifndef SGE_CELL_CIRCLE_LIST_HPP_INCLUDED
#define SGE_CELL_CIRCLE_LIST_HPP_INCLUDED

#include "circle.hpp"
#include <boost/intrusive/list.hpp>

namespace sge
{
namespace cell
{

typedef boost::intrusive::list<
	circle,
	boost::intrusive::constant_time_size<
		false
	>
> intrusive_circle_list;

}
}

#endif
