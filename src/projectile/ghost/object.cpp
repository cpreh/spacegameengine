#include "../declare_local_logger.hpp"
#include "../bullet_to_vector2.hpp"
#include "../vector2_to_bullet.hpp"
#include "../object_extrusion_depth.hpp"
#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/ghost/parameters.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/assert.hpp>
#include <boost/foreach.hpp>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

SGE_PROJECTILE_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("ghost"))

sge::projectile::ghost::object::object(
	parameters const &p)
:
	body_enter_(),
	body_exit_(),
	box_shape_(
		// The box shape gets _HALF EXTENTS_
		fcppt::make_unique_ptr<btBoxShape>(
			btVector3(
				p.size().get().w()/2,
				p.size().get().h()/2,
				object_extrusion_depth()))),
	ghost_object_(
		fcppt::make_unique_ptr<btPairCachingGhostObject>())
{
	FCPPT_LOG_DEBUG(
		local_log,
		fcppt::log::_ 
			<< this
			<< FCPPT_TEXT(": Created a new body, position ")
			<< p.position().get()
			<< FCPPT_TEXT(", size ")
			<< p.size().get());

	ghost_object_->setUserPointer(
		this);

	ghost_object_->setCollisionShape(
		box_shape_.get());
}

sge::projectile::vector2 const
sge::projectile::ghost::object::position() const
{
	return 
		bullet_to_vector2(
			ghost_object_->getWorldTransform().getOrigin());
}

void
sge::projectile::ghost::object::position(
	vector2 const &p)
{
	ghost_object_->setWorldTransform(
		btTransform(
			btMatrix3x3::getIdentity(),
			vector2_to_bullet(
				p)));
}

fcppt::signal::auto_connection
sge::projectile::ghost::object::body_enter(
	sge::projectile::ghost::body_enter const &f)
{
	return 
		body_enter_.connect(
			f);
}

fcppt::signal::auto_connection
sge::projectile::ghost::object::body_exit(
	sge::projectile::ghost::body_exit const &f)
{
	return 
		body_exit_.connect(
			f);
}

sge::projectile::ghost::object::~object()
{
}

void
sge::projectile::ghost::object::enter_internal(
	body::object const &b)
{
	body_enter_(
		b);
}

void
sge::projectile::ghost::object::exit_internal(
	body::object const &b)
{
	body_exit_(
		b);
}
