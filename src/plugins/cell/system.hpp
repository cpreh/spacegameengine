#ifndef SGE_CELL_SYSTEM_HPP_INCLUDED
#define SGE_CELL_SYSTEM_HPP_INCLUDED

#include <sge/collision/system.hpp>

namespace sge
{
namespace cell
{

class system : public collision::system {
public:
	world_ptr const
	create_world(
		collision::optional_rect const &);
};

}
}

#endif
