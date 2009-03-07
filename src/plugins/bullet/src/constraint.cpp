#include "../constraint.hpp"

sge::bullet::constraint::constraint(
	world_type &world,
	body_type &body,
	body_type &zero_body)
:
	world(world),
	constraint_(
		body,
		zero_body,
		btTransform::getIdentity(),
		btTransform::getIdentity(),
		false)
{
	// Use limit(axis, a, b) where a>b to disable limits on that axis
	constraint_.setLimit(0,1,0); // Disable X axis limits
	constraint_.setLimit(1,1,0); // Disable Y axis limits
	constraint_.setLimit(2,0,0); // Set the Z axis to always be equal to zero
	constraint_.setLimit(3,1,0); // Uncap the rotational axes
	constraint_.setLimit(4,1,0); // Uncap the rotational axes
	constraint_.setLimit(5,1,0); // Uncap the rotational axes

	world.addConstraint(&constraint_);
}

sge::bullet::constraint::~constraint()
{
	world.removeConstraint(&constraint_);
}
