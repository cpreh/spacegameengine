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
#ifndef SGE_CELL_CIRCLE_HPP_INCLUDED
#define SGE_CELL_CIRCLE_HPP_INCLUDED

#include "collision_callback.hpp"
#include <sge/collision/objects/circle.hpp>
#include <sge/collision/test_callback.hpp>
#include <sge/collision/satellite_fwd.hpp>
#include <sge/math/vector/basic_decl.hpp>
#include <sge/time/funit.hpp>
#include <boost/intrusive/list_hook.hpp>
#include <vector>

namespace sge
{
namespace cell
{

class grid;
class backlink;

class circle
:
	public collision::objects::circle,
	public boost::intrusive::list_base_hook<
		boost::intrusive::link_mode<
			boost::intrusive::auto_unlink
		>
	>
{
public:
	circle(
		collision::satellite_ptr,
		collision::point const &center,
		collision::point const &speed,
		collision::unit radius,
		grid &,
		collision::test_callback const &,
		collision_callback const &);
	
	void center(
		collision::point const &);
	
	collision::point const
	center() const;

	void speed(
		collision::point const &);
	
	collision::point const
	speed() const;

	collision::unit radius() const;
	collision::satellite &satellite();

	void update(
		time::funit);

	~circle();
private:
	void reposition();

	collision::satellite_ptr sat;

	collision::point
		center_,
		speed_;
	collision::unit const radius_;

	grid &grid_;

	typedef std::vector<
		backlink
	> backlink_vector;

	collision::test_callback const test_callback;
	collision_callback const callback;
	backlink_vector backlinks;
};

}
}

#endif
