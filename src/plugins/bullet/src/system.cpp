#include "../system.hpp"
#include "../world.hpp"

sge::collision::world_ptr const
sge::bullet::system::create_world(
	boost::optional<sge::collision::rect> const &r)
{
	return collision::world_ptr(
		new world());
}
