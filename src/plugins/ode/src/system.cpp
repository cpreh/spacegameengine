#include "../system.hpp"
#include "../world.hpp"
#include "../objects/circle.hpp"
#include <sge/structure_cast.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/cerr.hpp>
#include <cmath>

sge::ode::system::system()
{
	dInitODE();
}

sge::collision::world_ptr const sge::ode::system::create_world(
	boost::optional<collision::rect> const &r)
{
	return sge::collision::world_ptr(
		new world(r));
}

sge::ode::system::~system()
{
	dCloseODE();
}
