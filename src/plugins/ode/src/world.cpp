#include "../world.hpp"
#include "../body.hpp"
#include "../group.hpp"
#include "../shapes/circle.hpp"
#include <sge/collision/group_overflow.hpp>
#include <sge/math/null.hpp>
#include <sge/assert.hpp>
#include <sge/text.hpp>
#include <boost/ref.hpp>
#include <functional>
#include <cmath>

// DEBUG
#include <sge/cerr.hpp>

sge::ode::world::world(
	collision::optional_rect const &_r)
:
	world_(
		dWorldCreate()),
	space_(
		dHashSpaceCreate(
			0)), // <<- 0 for "no parent space"
	begin_signal_(),
	end_signal_(),
	test_signal_(
		std::logical_and<bool>()),
	group_id_(
		static_cast<group_id>(
			1)),
	time_remainder_(
		sge::math::null<dReal>()),
	collisions_(),
	transformer_(
		_r),
	body_count_(
		0)
{
	dWorldSetAutoDisableFlag(
		world_,
		1);
}

sge::signal::auto_connection
sge::ode::world::register_test_callback(
	collision::test_callback const &_c)
{
	return 
		test_signal_.connect(
			_c);
}

void
sge::ode::world::test_callback_combiner(
	collision::test_callback_combiner const &_c)
{
	test_signal_.combiner(
		_c);
}

sge::signal::auto_connection
sge::ode::world::register_begin_callback(
	collision::callback const &_c)
{
	return 
		begin_signal_.connect(
			_c);
}
	
sge::signal::auto_connection
sge::ode::world::register_end_callback(
	collision::callback const &_c)
{
	return
		end_signal_.connect(
			_c);
}
	
sge::collision::body_ptr const 
sge::ode::world::create_body(
	collision::satellite_ptr _satellite,
	collision::point const &_position,
	collision::point const &_linear_velocity)
{
	return 
		collision::body_ptr(
			new body(
				*this,
				transformer_,
				world_,
				_satellite,
				_position,
				_linear_velocity));
}

sge::collision::shapes::circle_ptr const
sge::ode::world::create_circle(
	collision::unit const _radius)
{
	return 
		collision::shapes::circle_ptr(
			new shapes::circle(
				transformer_,
				space_,
				_radius));
}

sge::collision::group_ptr const 
sge::ode::world::create_group()
{
	return
		collision::group_ptr(
			new group(
				next_group_id()));
}

void
sge::ode::world::update(
	collision::time_unit const deltan)
{
	dReal const delta = 
		static_cast<dReal>(deltan)+
		time_remainder_;
		
	dReal const time_step = 
		static_cast<dReal>(
			0.001);
	
	unsigned const iterations = 
		static_cast<unsigned>(
			delta/
			time_step);
			
	for (unsigned i = 0; i < iterations; ++i)
		step(
			time_step);
	
	time_remainder_ = 
		std::fmod(
			delta,
			time_step);
}

sge::ode::world::~world()
{
	SGE_ASSERT_MESSAGE(!body_count_,SGE_TEXT("You've tried to delete a world before all of its bodys are dead"));
	dSpaceDestroy(
		space_);
	dWorldDestroy(
		world_);
}

void sge::ode::world::step(
	dReal const _time_step)
{
	dSpaceCollide(
		space_,
		this,
		&static_collide);
	
	dWorldQuickStep(
	//dWorldStep(
		world_,
		_time_step);
	check_end_signals();
}

void sge::ode::world::check_end_signals()
{
	for (object_map::iterator it(collisions_.begin()),next(it); it != collisions_.end(); it = next)
	{
		++next;
		if (it->second)
		{
			it->second = false;
			continue;
		}
		
		call_signal(
			end_signal_,
			it->first.first,
			it->first.second);
				
		collisions_.erase(
			it);
	}
}

sge::ode::group_id sge::ode::world::next_group_id()
{
	if (group_id_ == static_cast<group_id>(1 << 31))
		throw collision::group_overflow();
	group_id const old = 
		group_id_;
	group_id_ <<= 1;
	return
		old;
}

void sge::ode::world::static_collide(
	void * const ptr,
	dGeomID const g0,
	dGeomID const g1)
{
	static_cast<world *>(ptr)->collide(
		g0,
		g1);
}

void sge::ode::world::collide(
	dGeomID const g0,
	dGeomID const g1)
{
	dBodyID const
		b0 = 
			dGeomGetBody(
				g0),
		b1 = 
			dGeomGetBody(
				g1);

	collision::satellite 
		&s0 = 
			*static_cast<body*>(
				dBodyGetData(
					b0))->satellite_,
		&s1 = 
			*static_cast<body*>(
				dBodyGetData(
					b1))->satellite_;
					
	if (!test_signal_(s0,s1))
	{
		sge::cerr << "test signal returned false\n";
		return;
	}
	
	//sge::cerr << "there was a collision!\n";
	// manual states that the contact array has to contain at least 1 element,
	// so to be sure, allocate one dContactGeom here
	dContactGeom g;
	if (!dCollide(g0,g1,1,&g,sizeof(dContactGeom)))
	{
		//sge::cerr << "but dcollide returned false :(\n";
		return;
	}
	
	std::pair<object_map::iterator,bool> 
		result = 
			collisions_.insert(
				std::make_pair(
					std::make_pair(
						b1 > b0 ? b0 : b1,
						b1 > b0 ? b1 : b0),
					true));
		
	// insertion was successful, so this collision is new. we then send a collision_begin
	if (result.second)
	{
		//sge::cerr << "inserting was successful\n";
		call_signal(
			begin_signal_,
			b0,
			b1);
	}
	// if it wasn't successful, then we shall update the timestamp for the later end-check
	else
	{
		//sge::cerr << "inserting was not sucessful\n";
		result.first->second = true;
	}
}

void sge::ode::world::call_signal(
	collision::callback_signal &s,
	dBodyID const b0,
	dBodyID const b1)
{
	collision::satellite 
		&s0 = 
			*static_cast<body*>(
				dBodyGetData(
					b0))->satellite_,
		&s1 = 
			*static_cast<body*>(
				dBodyGetData(
					b1))->satellite_;
					
	s(
		boost::ref(
			s0),
		boost::ref(
			s1));
}

void sge::ode::world::destroy_body(
	dBodyID const _body)
{
	for (object_map::iterator it(collisions_.begin()),next(it); it != collisions_.end(); it = next)
	{
		++next;
		
		if (it->first.first == _body || it->first.second == _body)
			collisions_.erase(
				it);
	}
}
