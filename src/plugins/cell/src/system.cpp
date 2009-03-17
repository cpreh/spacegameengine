#include "../system.hpp"
#include "../world.hpp"
#include <sge/make_shared_ptr.hpp>

sge::collision::world_ptr const
sge::cell::system::create_world(
	collision::optional_rect const &rect)
{
	return make_shared_ptr<
		world
	>(
		rect
	);
}

