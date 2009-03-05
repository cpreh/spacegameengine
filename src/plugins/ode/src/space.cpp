#include "../space.hpp"

sge::ode::space::space(
	boost::optional<collision::rect> const &_rect)
	: id_()
{
	if (!_rect)
	{
		id_ = dHashSpaceCreate(0);
	}
	else
	{
		collision::rect const r = *_rect;
		dVector3 center;
		center[0] = static_cast<dReal>(r.left() + r.w()/2);
		center[1] = static_cast<dReal>(r.top() + r.h()/2);
		center[2] = static_cast<dReal>(0);
		dVector3 extents;
		extents[0] = static_cast<dReal>(r.w());
		extents[1] = static_cast<dReal>(r.h());
		extents[2] = static_cast<dReal>(0);
		id_ = dQuadTreeSpaceCreate(
			0, 
			center, 
			extents, 
			3);
	}
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
