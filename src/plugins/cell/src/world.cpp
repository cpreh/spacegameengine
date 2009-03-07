#include "../world.hpp"
#include "../circle.hpp"
#include "../grid_entry.hpp"
#include <sge/collision/satellite.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

sge::cell::world::world(
	collision::optional_rect const &rect)
:
	grid_(
		rect
		? *rect
		: collision::rect(
			0,
			0,
			1000,
			1000
		)
	)
{}

void
sge::cell::world::test_callback(
	::sge::collision::test_callback const &cb)
{
	test_callback_ = cb;
}

sge::signals::connection const 
sge::cell::world::register_callback(
	collision::callback const &cb)
{
	return sig.connect(
		cb
	);
}
	
sge::collision::objects::circle_ptr const
sge::cell::world::create_circle(
	collision::satellite_ptr sat,
	collision::point const &center,
	collision::point const &speed,
	collision::unit const radius)
{
	return collision::objects::circle_ptr( //make_shared_ptr<
		new circle(
	//>(
		sat,
		center,
		speed,
		radius,
		grid_,
		boost::bind(
			&world::call_test,
			this,
			_1,
			_2
		),
		sig
	));
}

void
sge::cell::world::update(
	collision::time_unit const delta)
{
	grid_.update(
		delta);
}

bool
sge::cell::world::call_test(
	collision::satellite const &a,
	collision::satellite const &b)
{
	return test_callback_
		? test_callback_(
			a,
			b
		)
		: false;
}
