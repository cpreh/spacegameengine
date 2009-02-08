#include "../motion_state.hpp"
#include "../conversion.hpp"

namespace
{
btTransform const make_transform(sge::bullet::point const &p)
{
	btTransform t;
	t.setIdentity();
	t.setOrigin(p);
	return t;
}
}

sge::bullet::motion_state::motion_state(change_callback const &_callback)
	: pos_(
			make_transform(
				point(
					static_cast<unit>(0),
					static_cast<unit>(0),
					static_cast<unit>(0)))),
		callback(_callback)
{
}

void sge::bullet::motion_state::pos(point const &v)
{
	pos_ = make_transform(v);
	callback(v);
}

sge::bullet::point const sge::bullet::motion_state::pos() const
{
	return pos_.getOrigin();
}

void sge::bullet::motion_state::getWorldTransform(btTransform &t) const
{
	t = pos_;
}

// called only by bullet internally
void sge::bullet::motion_state::setWorldTransform(btTransform const &t)
{
	pos_ = t;
	callback(pos_.getOrigin());
}
