#ifndef SGE_CELL_CIRCLE_LIST_HPP_INCLUDED
#define SGE_CELL_CIRCLE_LIST_HPP_INCLUDED

#include <list>

class circle;

namespace sge
{
namespace cell
{

typedef std::list<
	circle *
> circle_list;

}
}

#endif
