#include "../circle.hpp"
#include "../collides.hpp"
#include "../grid.hpp"
#include "../grid_entry.hpp"
#include "../backlink.hpp"
#include <sge/collision/satellite.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <boost/foreach.hpp>

sge::cell::circle::circle(
	collision::satellite_ptr sat,
	collision::point const &center_,
	collision::point const &speed_,
	collision::unit const radius_,
	grid &grid_,
	collision::test_callback const &test_callback,
	collision::callback_signal &callback)
:
	sat(sat),
	center_(center_),
	speed_(speed_),
	radius_(radius_),
	grid_(grid_),
	backlinks(),
	test_callback(test_callback),
	callback(callback)
{
	reposition();
}

void
sge::cell::circle::center(
	collision::point const &ncenter)
{
	center_ = ncenter;
}

sge::collision::point const
sge::cell::circle::center() const
{
	return center_;
}

void
sge::cell::circle::speed(
	collision::point const &nspeed)
{
	speed_ = nspeed;
}

sge::collision::point const
sge::cell::circle::speed() const
{
	return speed_;
}

sge::collision::satellite &
sge::cell::circle::satellite()
{
	return *sat;
}

void
sge::cell::circle::update(
	time::funit const delta)
{
	center_ += speed_ * delta;
	
	reposition();

	BOOST_FOREACH(
		backlink_list::reference r,
		backlinks
	)
	{
		grid_entry &e(
			r.entry()
		);
		
		BOOST_FOREACH(
			circle_list::reference circ,
			e.entries()
		)
		{
			if(
				test_callback(
					circ->satellite(),
					satellite()
				)
				&& collides(
					*circ,
					*this
				)
			)
				callback(
					circ->satellite(),
					satellite()
				);
		}
	}
}

sge::cell::circle::~circle()
{}

void
sge::cell::circle::reposition()
{
	// TODO: optimize this!

	field_type &field(
		grid_.field()
	);

	backlinks.clear();

	for(
		collision::unit x = center().x() - radius();
		x < center().x() + radius();
		x += grid_.cell_size().w()
	)
		for(
			collision::unit y = center().y() - radius();
			y < center().y() + radius();
			y += grid_.cell_size().h()
		)
		{
			grid_entry &e(
				field.pos(
					static_cast<field_type::size_type>(x / grid_.cell_size().w()),
					static_cast<field_type::size_type>(y / grid_.cell_size().h())
				)
			);

			circle_list list(
				e.entries()
			);

			backlinks.push_back(
				backlink(
					e,
					list.insert(
						list.begin(),
						this
					)
				)
			);
		}
}
