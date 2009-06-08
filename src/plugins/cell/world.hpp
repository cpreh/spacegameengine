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


#ifndef SGE_CELL_WORLD_HPP_INCLUDED
#define SGE_CELL_WORLD_HPP_INCLUDED

#include "grid.hpp"
#include "intrusive_circle_list.hpp"
#include <sge/collision/world.hpp>
#include <sge/collision/time_unit.hpp>
#include <sge/collision/optional_rect.hpp>

namespace sge
{
namespace cell
{

class circle;

class world : public collision::world {
public:
	explicit world(
		collision::optional_rect const &);

	~world();

	void
	test_callback(
		collision::test_callback const &);

	signal::auto_connection
	register_callback(
		collision::callback const &);
	
	collision::objects::circle_ptr const
	create_circle(
		collision::satellite_ptr,
		collision::point const &center,
		collision::point const &speed,
		collision::unit radius);

	void
	update(
		collision::time_unit delta);
private:
	bool call_test(
		collision::satellite const &,
		collision::satellite const &
	);

	void on_collide(
		circle &,
		circle &);

	grid grid_;
	bool test_running;
	intrusive_circle_list objects;
	collision::callback_signal sig;
	collision::test_callback test_callback_;
};

}
}

#endif
