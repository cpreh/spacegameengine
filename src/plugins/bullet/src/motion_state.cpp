#include "../motion_state.hpp"
#include "../conversion.hpp"
#include <sge/math/vector/vector.hpp>
#include <sge/math/vector/output.hpp>
#include <sge/cerr.hpp>

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
	//sge::cerr << "externally setting new position to: " << v.x() << "x" << v.y() << "x" << v.z() << "\n";
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
	if (bullet_to_sge(t.getOrigin()) == sge::collision::point::null())
		sge::cerr << "bullet set new position to: " << bullet_to_sge(t.getOrigin()) << "\n";
	//pos_ = t;
	pos_ = make_transform(t.getOrigin());
	callback(pos_.getOrigin());
}
