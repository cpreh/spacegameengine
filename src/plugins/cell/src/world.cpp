#include "../world.hpp"
#include <sge/make_shared_ptr.hpp>
#include <boost/bind.hpp>

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
	test_callback = cb;
}

sge::signals::connection const 
sge::cell::world::register_callback(
	callback const &cb)
{
	return sig.connect(
		cb
	);
}
	
sge::collision::objects::circle_ptr const
sge::cell::world::create_circle(
	sattelite_ptr sat,
	point const &center,
	point const &speed,
	unit const radius)
{
	return make_shared_ptr<
		circle
	>(
		sat,
		center,
		speed,
		radius,
		grid_,
		sig,
		boost::bind(
			&world::call_test,
			this,
			_1,
			_2
		)
	);
}

void
sge::cell::world::update(
	time::funit const delta)
{
	grid_.update(
		delta);
}

bool
sge::cell::world::call_test(
	collision::satellite &a,
	collision::satellite &b)
{
	return test_callback
		? test_callback(
			a,
			b
		)
		: false;
}
