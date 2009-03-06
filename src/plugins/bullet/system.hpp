#ifndef SGE_BULLET_SYSTEM_HPP_INCLUDED
#define SGE_BULLET_SYSTEM_HPP_INCLUDED

#include <sge/collision/system.hpp>

namespace sge
{
namespace bullet
{
class system : public sge::collision::system
{
public:
	sge::collision::world_ptr const create_world(
		boost::optional<sge::collision::rect> const &);
};
}
}

#endif
