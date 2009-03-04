#include "../space.hpp"

sge::ode::space::space()
	: id_(dHashSpaceCreate(0))
	//: id_(dSimpleSpaceCreate(0))
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
