#include "motion_state.hpp"
#include <sge/projectile/body/object.hpp>

sge::projectile::body::detail::motion_state::motion_state(
	object &_body)
:
	body_(
		_body)
{
}

sge::projectile::body::detail::motion_state::~motion_state()
{
}

void	
sge::projectile::body::detail::motion_state::getWorldTransform(
	btTransform &t) const
{
	body_.getWorldTransform(
		t);
}

void	
sge::projectile::body::detail::motion_state::setWorldTransform(
	btTransform const &t)
{
	body_.setWorldTransform(
		t);
}
