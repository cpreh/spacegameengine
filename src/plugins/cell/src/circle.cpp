#include "../circle.hpp"
#include "../collides.hpp"
#include "../grid.hpp"
#include <boost/foreach.hpp>

sge::cell::circle::circle(
	satellite_ptr sat,
	point const &center_,
	point const &speed_,
	unit const radius_,
	grid &grid_,
	collision::test_callback const &test_callback,
	collision::callback_signal const &callback)
:
	sat(sat),
	center_(center_),
	speed_(speed_),
	radius_(radius_),
	test_callback(test_callback),
	callback(callback),
	grid_(grid_),
	backlinks(),
	test_callback(test_callback),
	callback(callback)
{
	reposition();
}

void
sge::cell::circle::center(
	point const &center_)
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
	point const &nspeed)
{
	speed_ = nspeed;
}

sge::collision::point const
sge::cell::circle::speed() const
{
	return speed_;
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
			weak_circle_list::reference circ,
			e.entries()
		)
		{
			if(
				test_callback(
					circ->satellite(),
					sattelite()
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
		collision::unit x = center().x() - radius;
		x < center().x() + radius;
		x += grid.cell_size().w()
	)
		for(
			collision::unit y = center().y() - radius;
			y < center().y() + radius;
			y += grid.cell_size().h()
		)
		{
			grid_entry &e(
				field.at_xy(
					x / grid.cell_size.w(),
					y / grid.cell_size.h()
				)
			);

			circle_list list(
				e.entries()
			);

			backlinks.push_back(
				e,
				list.insert(
					list.begin(),
					this
				)
			);
		}
}
