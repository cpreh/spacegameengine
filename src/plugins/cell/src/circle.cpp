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
#include "../circle.hpp"
#include "../collides.hpp"
#include "../grid.hpp"
#include "../grid_entry.hpp"
#include "../backlink.hpp"
#include <sge/collision/satellite.hpp>
#include <sge/container/field_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/dim.hpp>
#include <sge/math/vector/structure_cast.hpp>
#include <boost/foreach.hpp>

sge::cell::circle::circle(
	collision::satellite_ptr sat,
	collision::point const &center_,
	collision::point const &speed_,
	collision::unit const radius_,
	grid &grid_,
	collision::test_callback const &test_callback,
	collision_callback const &callback)
:
	sat(sat),
	center_(center_),
	speed_(speed_),
	radius_(radius_),
	grid_(grid_),
	test_callback(test_callback),
	callback(callback),
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
				&circ != this
				&& test_callback(
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
{}

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
			grid::pos_type const pos(
				(grid::pos_type(
					x,
					y
				) - grid_.pos()) / grid_.cell_size()
			);

			field_type::vector_type const fpos(
				math::vector::structure_cast<
					field_type::vector_type
				>(
					pos
				)
			);

			if(
				pos.x() < 0
				|| pos.y() < 0
				|| fpos.x() >= field.dim().w()
				|| fpos.y() >= field.dim().h()
			)
				continue;
			
			grid_entry &e(
				field.pos(
					fpos
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
