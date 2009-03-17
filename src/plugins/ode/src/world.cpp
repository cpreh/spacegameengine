#include "../world.hpp"
#include "../objects/circle.hpp"
#include <sge/collision/satellite.hpp>
#include <boost/ref.hpp>

sge::ode::world::world(
	collision::optional_rect const &p)
:
	world_(),
	space_(p)
{
	// this could be set to disable the auto disable feature
	dWorldSetAutoDisableFlag(world_.id(),0);
	dSpaceCollide(space_.id(),this,&internal_static_collide);
}

void
sge::ode::world::test_callback(
	::sge::collision::test_callback const &_test_callback)
{
	test_callback_ = _test_callback;
}

sge::signal::auto_connection
sge::ode::world::register_callback(
	collision::callback const &c)
{
	return callback_.connect(c);
}

sge::collision::objects::circle_ptr const
sge::ode::world::create_circle(
	collision::satellite_ptr _satellite,
	collision::point const &center,
	collision::point const &speed,
	collision::unit radius)
{
	return sge::collision::objects::circle_ptr(
		new objects::circle(
			_satellite,
			space_,
			world_,
			structure_cast<point>(center),
			structure_cast<point>(speed),
			static_cast<dReal>(radius)));
}

void
sge::ode::world::update(
	collision::time_unit const delta)
{
	collision::time_unit const step_size = static_cast<collision::time_unit>(0.0001);
	//unsigned iterations = static_cast<unsigned>(std::ceil(delta/step_size));
	unsigned iterations = static_cast<unsigned>(delta/step_size);
	//if (iterations == 0)
	//	iterations = 1;

	dSpaceCollide(space_.id(),this,&internal_static_collide);

	//sge::cerr << "step size is " << step_size << ", delta is " << delta << ", doing " << iterations << " iterations\n";

	for (unsigned i = 0; i < iterations; ++i)
		dWorldStep(
			world_.id(),
			static_cast<dReal>(
				step_size));

	//dWorldQuickStep(dWorldID, dReal stepsize);
}

void sge::ode::world::internal_static_collide(void *data,dGeomID g1,dGeomID g2)
{
	static_cast<world *>(data)->internal_collide(g1,g2);
}

void sge::ode::world::internal_collide(dGeomID g1,dGeomID g2)
{
	if (!test_callback_)
		return;
	
	collision::satellite &s1 = 
		*static_cast<collision::satellite*>(dGeomGetData(g1));
	collision::satellite &s2 = 
		*static_cast<collision::satellite*>(dGeomGetData(g2));

	if (test_callback_(s1,s2))
	{
		// manual states that the contact array has to contain at least 1 element,
		// so to be sure, allocate one dContactGeom here
		dContactGeom g;
		if (dCollide(g1,g2,1,&g,sizeof(dContactGeom)))
			callback_(
				boost::ref(
					s1
				),
				boost::ref(
					s2
				)
			);
	}
}
