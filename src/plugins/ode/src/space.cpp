#include "../space.hpp"

sge::ode::space::space()
	: id_(dHashSpaceCreate())
{
}

dSpaceID &sge::ode::space::id()
{
	return id_;
}

dSpaceID const &sge::ode::space::id() const
{
	return id_;
}

sge::ode::space::~space()
{
	dSpaceDestroy(id_);
}
