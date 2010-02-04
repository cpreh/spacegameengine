#include "../world.hpp"
#include "../unit.hpp"
#include "../body.hpp"
#include "../convert/to_bullet.hpp"
#include "../shapes/sphere.hpp"
#include "../shapes/box.hpp"
#include "../group.hpp"
#include "../log.hpp"
#include <sge/collision/group_overflow.hpp>
#include <sge/collision/satellite.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/tr1/functional.hpp>
#include <boost/foreach.hpp>
#include <limits>

namespace
{
fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("world")));
}

sge::bullet::world::world(
	collision::optional_box const &,
	collision::constraint::type const _constrain)
:
	configuration_(),
	dispatcher_(
		&configuration_),
	broadphase_(),
	constraint_solver_(),
	world_(
		&dispatcher_,
		&broadphase_,
		&constraint_solver_,
		&configuration_),
	constrain_(
		_constrain),
	overlap_filter_(),
	body_manager_(
		*this),
	group_id_(
		static_cast<group_id>(
			1))
{
	// bullet sets the default gravity to (0,-10,0) so we counteract this
	world_.setGravity(
		convert::to_bullet(
			point::null()));
	world_.getPairCache()->setOverlapFilterCallback(
		&overlap_filter_);
}

fcppt::signal::auto_connection
sge::bullet::world::register_test_callback(
	collision::test_callback const &f)
{
	return
		overlap_filter_.register_callback(
			f);
}

void 
sge::bullet::world::test_callback_combiner(
	collision::test_callback_combiner const &c)
{
	overlap_filter_.combiner(
		c);
}

fcppt::signal::auto_connection
sge::bullet::world::register_begin_callback(
	collision::shape_callback const &f)
{
	return 
		body_manager_.register_begin(
			f);
}
	
fcppt::signal::auto_connection
sge::bullet::world::register_end_callback(
	collision::shape_callback const &f)
{
	return 
		body_manager_.register_end(
			f);
}

fcppt::signal::auto_connection
sge::bullet::world::register_solid_callback(
	collision::shape_callback const &f)
{
	return 
		body_manager_.register_solid(
			f);
}
	
sge::collision::body_ptr const 
sge::bullet::world::create_body(
	collision::shapes::container const &_shapes,
	collision::point const &_position,
	collision::point const &_linear_velocity)
{
	return 
		collision::body_ptr(
			new body(
				*this,
				_shapes,
				fcppt::math::vector::structure_cast<point>(
					_position),
				fcppt::math::vector::structure_cast<point>(
					_linear_velocity)));
}

sge::collision::shapes::sphere_ptr const
sge::bullet::world::create_sphere(
	collision::satellite_ptr _satellite,
	collision::unit const _radius,
	collision::solidity::type const _solidity,
	collision::point const &_position)
{
	return 
		collision::shapes::sphere_ptr(
			new shapes::sphere(
				_satellite,
				constrain_,
				*this,
				_radius,
				_solidity,
				_position));
}

sge::collision::shapes::box_ptr const
sge::bullet::world::create_box(
	collision::satellite_ptr _satellite,
	collision::dim const &_dim,
	collision::solidity::type const _solidity,
	collision::point const &_position)
{
	return
		collision::shapes::box_ptr(
			new shapes::box(
				_satellite,
				constrain_,
				*this,
				_position,
				_solidity,
				_dim));
}

sge::collision::group_ptr const 
sge::bullet::world::create_group()
{
	return 
		collision::group_ptr(
			new group(
				next_group_id()));
}

void
sge::bullet::world::update(
	collision::time_unit const delta)
{
	unit const fixed_step = 
		static_cast<btScalar>(1)/
		static_cast<btScalar>(60);
	
	BOOST_FOREACH(solid_collision_set::const_reference r,solid_collisions_)
		r->velocity_change();
	solid_collisions_.clear();
	
	world_.stepSimulation(
		delta,
		std::numeric_limits<int>::max(),
		//2,
		fixed_step);
		
	BOOST_FOREACH(
		shapes::base *s,
		queued_shapes_)
		s->insert_into_world();
	queued_shapes_.clear();
}

void
sge::bullet::world::collides_with(
	collision::group_ptr const a,
	collision::group_ptr const b)
{
	dynamic_cast<group &>(*a).collides_with(
		dynamic_cast<group &>(*b));
	dynamic_cast<group &>(*b).collides_with(
		dynamic_cast<group &>(*a));
}

void 
sge::bullet::world::queue_add_shape(
	shapes::base &_s)
{
	queued_shapes_.insert(
		&_s);
}

void 
sge::bullet::world::add_shape(
	btRigidBody &_body)
{
	world_.addRigidBody(
		&_body);
}

void
sge::bullet::world::reset_shape(
	btRigidBody &_body)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Resetting shape. This shape is static: ")
			<< _body.isStaticObject());
	world_.removeRigidBody(
		&_body);
	world_.addRigidBody(
		&_body);
}

void 
sge::bullet::world::remove_shape(
	btRigidBody &_body,
	shapes::base &_shape)
{
	world_.removeRigidBody(
		&_body);
	solid_collisions_.erase(
		&_shape);
}

sge::bullet::collision_proxy const &
sge::bullet::world::collision_begin(
	btManifoldPoint &cp,
	shapes::base &a,
	shapes::base &b)
{
	return 
		body_manager_.begin(
			cp,
			a,
			b);
}
	
void
sge::bullet::world::collision_end(
	shapes::base &a,
	shapes::base &b)
{
	body_manager_.end(
		a,
		b);
}

void
sge::bullet::world::solid_collision(
	shapes::base &a,
	shapes::base &b)
{
	// has_meta_body == !is_static
	if (a.has_meta_body())
		solid_collisions_.insert(
			&a);
			
	if (b.has_meta_body())
		solid_collisions_.insert(
			&b);
}

sge::bullet::group_id
sge::bullet::world::next_group_id()
{
	if (group_id_ == static_cast<group_id>(1 << 15))
		throw collision::group_overflow();
	group_id const old = group_id_;
	// <<= doesn't work because of -Wconversion
	group_id_ = 
		static_cast<group_id>(
			group_id_ << 1);
	return old;
}
