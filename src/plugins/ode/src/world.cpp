#include "../world.hpp"
#include "../objects/circle.hpp"

sge::ode::world::world(
	boost::optional<collision::rect> const &p)
	: world_(),
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

sge::signals::connection const 
sge::ode::world::register_callback(
	collision::callback const &c)
{
	return callback_.connect(c);
}

sge::collision::objects::circle_ptr const
sge::ode::world::create_circle(
	collision::sattelite_ptr _sattelite,
	collision::point const &center,
	collision::point const &speed,
	collision::unit radius)
{
	return sge::collision::objects::circle_ptr(
		new objects::circle(
			_sattelite,
			space_,
			world_,
			structure_cast<point>(center),
			structure_cast<point>(speed),
			static_cast<dReal>(radius)));
}

void
sge::ode::world::update(
	time::funit delta)
{
	time::funit const step_size = static_cast<time::funit>(0.0001);
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
	
	collision::sattelite &s1 = 
		*static_cast<collision::sattelite*>(dGeomGetData(g1));
	collision::sattelite &s2 = 
		*static_cast<collision::sattelite*>(dGeomGetData(g2));

	if (test_callback_(s1,s2))
	{
		// manual states that the contact array has to contain at least 1 element,
		// so to be sure, allocate one dContactGeom here
		dContactGeom g;
		if (dCollide(g1,g2,1,&g,sizeof(dContactGeom)))
		{
			callback_(s1,s2);
		}
	}
}
