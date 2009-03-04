#include "../world.hpp"

sge::ode::world::world()
	 : id_(dWorldCreate())
{
}

dWorldID &sge::ode::world::id()
{
	return id_;
}

dWorldID const &sge::ode::world::id() const
{
	return id_;
}

sge::ode::world::~world()
{
	dWorldDestroy(id_);
}
