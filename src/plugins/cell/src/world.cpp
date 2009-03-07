#include "../world.hpp"
#include "../circle.hpp"
#include "../grid_entry.hpp"
#include <sge/collision/satellite.hpp>
#include <sge/make_shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/next_prior.hpp>

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
	),
	objects(),
	current_it(
		objects.end()
	)
{}

sge::cell::world::~world()
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
	return make_shared_ptr<
		circle
	>(
		boost::ref(
			sat
		),
		center,
		speed,
		radius,
		boost::ref(
			grid_
		),
		boost::bind(
			&world::call_test,
			this,
			_1,
			_2
		),
		boost::ref(
			sig
		),
		boost::bind(
			&world::register_,
			this,
			_1
		),
		boost::bind(
			&world::unregister,
			this,
			_1
		)
	);
}

void
sge::cell::world::update(
	collision::time_unit const delta)
{
	current_it = objects.begin();
	for(
		;
		current_it != objects.end();
		++current_it
	)
		(*current_it)->update(
			delta
		);
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

sge::cell::circle_list::iterator
sge::cell::world::register_(
	circle &c)
{
	return objects.insert(
		objects.begin(),
		&c
	);
}

void
sge::cell::world::unregister(
	circle_list::iterator const it)
{
	if(it == current_it)
		current_it =
			current_it == objects.begin()
			? objects.begin()
			: boost::prior(it);
	objects.erase(it);
}
