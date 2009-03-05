#include "../world_wrapper.hpp"

sge::ode::world_wrapper::world_wrapper()
	 : id_(dWorldCreate())
{
}

dWorldID &sge::ode::world_wrapper::id()
{
	return id_;
}

dWorldID const &sge::ode::world_wrapper::id() const
{
	return id_;
}

sge::ode::world_wrapper::~world_wrapper()
{
	dWorldDestroy(id_);
}
