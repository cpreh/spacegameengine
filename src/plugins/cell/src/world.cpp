/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
#include "../world.hpp"
#include "../circle.hpp"
#include "../grid_entry.hpp"
#include <sge/collision/satellite.hpp>
#include <sge/math/rect/basic_impl.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/optional.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <boost/foreach.hpp>

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
	test_running(false),
	objects(),
	sig(),
	test_callback_()
{}

sge::cell::world::~world()
{}

void
sge::cell::world::test_callback(
	::sge::collision::test_callback const &cb)
{
	test_callback_ = cb;
}

sge::signal::auto_connection
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
	shared_ptr<
		circle
	> const ptr(
		 make_shared_ptr<
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
			boost::bind(
				&world::on_collide,
				this,
				_1,
				_2
			)
		)
	);

	objects.push_back(*ptr);
	return ptr;
}

void
sge::cell::world::update(
	collision::time_unit const delta)
{
	// TODO: use scoped_exit here!
	test_running = true;

	BOOST_FOREACH(
		intrusive_circle_list::reference r,
		objects	
	)
		r.update(
			delta
		);
	
	test_running = false;
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

void 
sge::cell::world::on_collide(
	circle &a,
	circle &b)
{
	sig(
		boost::ref(a.satellite()),
		boost::ref(b.satellite())
	);
}
