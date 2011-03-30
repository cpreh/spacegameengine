#include <sge/projectile/group/object.hpp>
#include <sge/projectile/group/id.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/world.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

sge::projectile::group::object::object(
	world &_world)
:
	category_(
		_world.next_group_id()),
	collides_(
		// a valid static_cast since id is short! Winning.
		static_cast<id>(
			0)),
	dirty_(
		false)
{
}

void
sge::projectile::group::object::add_body(
	body::object &_body)
{
	FCPPT_ASSERT(
		_body.body_->getBroadphaseProxy());
	_body.body_->getBroadphaseProxy()->m_collisionFilterGroup |= category_;
	_body.body_->getBroadphaseProxy()->m_collisionFilterMask |= collides_;
	dirty_ = true;
}

void
sge::projectile::group::object::add_ghost(
	ghost::object &_ghost)
{
	FCPPT_ASSERT(
		_ghost.ghost_object_->getBroadphaseHandle());
	_ghost.ghost_object_->getBroadphaseHandle()->m_collisionFilterGroup |= category_;
	_ghost.ghost_object_->getBroadphaseHandle()->m_collisionFilterMask |= collides_;
	dirty_ = true;
}

sge::projectile::group::object::~object()
{
}

void
sge::projectile::group::object::collides_with(
	object const &other)
{
	FCPPT_ASSERT_MESSAGE(
		!dirty_,
		FCPPT_TEXT("You tried to modify the group after a body has already been added to it. That's an inconsistency, please fix this in your code."));
	collides_ |= other.category_;
}
