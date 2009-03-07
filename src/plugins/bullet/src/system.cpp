#include "../system.hpp"
#include "../world.hpp"

sge::collision::world_ptr const
sge::bullet::system::create_world(
	collision::optional_rect const &r)
{
	return collision::world_ptr(
		new world());
}
