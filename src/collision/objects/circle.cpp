#include <sge/collision/objects/circle.hpp>
#include <sge/math/vector/vector.hpp>

sge::collision::objects::circle::circle()
{}

void sge::collision::objects::circle::pos(point const &p)
{
	center(p);
}

sge::collision::point const sge::collision::objects::circle::pos() const
{
	return center();
}

sge::collision::objects::circle::~circle()
{}
