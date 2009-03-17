#include "../system.hpp"
#include "../world.hpp"
#include <sge/make_shared_ptr.hpp>

sge::ode::system::system()
{
	dInitODE();
}

sge::collision::world_ptr const
sge::ode::system::create_world(
	collision::optional_rect const &r)
{
	return make_shared_ptr<
		world
	>(
		r
	);
}

sge::ode::system::~system()
{
	dCloseODE();
}
