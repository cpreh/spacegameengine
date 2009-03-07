#include "../circle.hpp"
#include "../collides.hpp"
#include "../grid.hpp"
#include "../grid_entry.hpp"
#include "../backlink.hpp"
#include <sge/collision/satellite.hpp>
#include <sge/container/field_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/dim.hpp>
#include <sge/structure_cast.hpp>
#include <boost/foreach.hpp>

sge::cell::circle::circle(
	collision::satellite_ptr sat,
	collision::point const &center_,
	collision::point const &speed_,
	collision::unit const radius_,
	grid &grid_,
	collision::test_callback const &test_callback,
	collision_callback const &callback,
	register_callback const &register_,
	unregister_callback const &unregister_)
:
	sat(sat),
	center_(center_),
	speed_(speed_),
	radius_(radius_),
	grid_(grid_),
	test_callback(test_callback),
	callback(callback),
	register_(register_),
	unregister_(unregister_),
	list_pos(
		register_(
			*this
		)
	),
	backlinks()
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

sge::collision::unit
sge::cell::circle::radius() const
{
	return radius_;
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

	satellite().position_change(
		center()
	);
	
	reposition();

	BOOST_FOREACH(
		backlink_vector::reference r,
		backlinks
	)
	{
		grid_entry &e(
			r.entry()
		);
		
		BOOST_FOREACH(
			intrusive_backlink_list::reference link,
			e.entries()
		)
		{
			circle &circ(
				link.circle()
			);

			if(
				test_callback(
					circ.satellite(),
					satellite()
				)
				&& collides(
					circ,
					*this
				)
			)
				callback(
					circ,
					*this
				);
		}
	}
}

sge::cell::circle::~circle()
{
	unregister_(
		list_pos
	);
}

void
sge::cell::circle::reposition()
{
	// TODO: optimize this!
	backlinks.clear();

	field_type &field(
		grid_.field()
	);

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
					sge::structure_cast<
						field_type::vector_type
					>(
						(grid::pos_type(
							x,
							y
						) - grid_.pos()) / grid_.cell_size()
					)
				)
			);

			backlinks.push_back(
				backlink(
					e,
					*this
				)
			);
		}
}
