#include "../body.hpp"
#include "../shapes/base.hpp"
#include "../world.hpp"
#include "../transformer_impl.hpp"
#include <sge/math/vector/basic_decl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/collision/satellite.hpp>

// DEBUG
#include <sge/cerr.hpp>
#include <sge/math/vector/output.hpp>

sge::ode::body::body(
	world &_world,
	transformer const &_transformer,
	dWorldID const _worldid,
	collision::satellite_ptr _satellite,
	collision::point const &_position,
	collision::point const &_linear_velocity)
:
	world_(
		_world),
	transformer_(
		_transformer),
	body_(
		dBodyCreate(
			_worldid)),
	satellite_(
		_satellite)
{
	//sge::cerr << "ode: created a body " << this << " at position " << _position << " with velocity " << _linear_velocity;
	world_.body_count_++;
	dBodySetData(
		body_,
		this);
	dBodySetMovedCallback(
		body_,
		&body::moved);
	position(
		_position);
	linear_velocity(
		_linear_velocity);
}

sge::collision::point const sge::ode::body::position() const
{
	dReal const * const p = 
		dBodyGetPosition(
			body_);
	return 
		transformer_.position_from_ode(
			point(
				p[0],
				p[1],
				p[2]));
	
}

void sge::ode::body::position(
	collision::point const &_p)
{
	//sge::cerr << "ode: body " << this << " position was set to " << _p << "\n";
	point const p = 
		transformer_.position_to_ode(
			_p);
	dBodySetPosition(
		body_,
		p.x(),
		p.y(),
		p.z());
}

sge::collision::point const sge::ode::body::linear_velocity() const
{
	dReal const * const p = 
		dBodyGetLinearVel(
			body_);
	return 
		transformer_.velocity_from_ode(
			point(
				p[0],
				p[1],
				p[2]));
}

void sge::ode::body::linear_velocity(
	collision::point const &_p)
{
	//sge::cerr << "ode: body " << this << " velocity was set to " << _p << "\n";
	point const p = 
		transformer_.velocity_to_ode(
			_p);
	dBodySetLinearVel(
		body_,
		p.x(),
		p.y(),
		p.z());
}

void sge::ode::body::add(
	collision::shapes::base_ptr const _s)
{
	//sge::cerr << "ode: adding shape to body " << this << "\n";
	dynamic_cast<ode::shapes::base &>(
		*_s).assign_body(body_);
}

bool sge::ode::body::is_active()
{
	return 
		dBodyIsEnabled(
			body_);
}

void sge::ode::body::is_active(
	bool const _b)
{
	if (_b)
		dBodyEnable(
			body_);
	else
		dBodyDisable(
			body_);
}

sge::ode::body::~body()
{
	//sge::cerr << "destroyed a body " << this << " \n";
	world_.body_count_--;
	world_.destroy_body(
		body_);
	dBodyDestroy(
		body_);
}

void sge::ode::body::moved(
	dBodyID const _body)
{
	dReal const *const p = 
		dBodyGetPosition(
			_body);
	body &b =
		*static_cast<body *>(
			dBodyGetData(
				_body));
	b.satellite_->position_change(
		b.transformer_.position_from_ode(
			point(
				p[0],
				p[1],
				p[2])));
}
