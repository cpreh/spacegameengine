#ifndef SGE_CELL_BACKLINK_LIST_HPP_INCLUDED
#define SGE_CELL_BACKLINK_LIST_HPP_INCLUDED

#include <list>

namespace sge
{
namespace cell
{

class backlink;

typedef std::list<
	backlink
> backlink_list;

}
}

#endif
