#ifndef SGE_CELL_CIRCLE_LIST_HPP_INCLUDED
#define SGE_CELL_CIRCLE_LIST_HPP_INCLUDED

#include <list>

namespace sge
{
namespace cell
{

class circle;

typedef std::list<
	circle *
> circle_list;

}
}

#endif
