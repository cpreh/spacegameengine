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

#ifndef SGE_ODE_WORLD_HPP_INCLUDED
#define SGE_ODE_WORLD_HPP_INCLUDED

#include "transformer.hpp"
#include "point.hpp"
#include "group_id.hpp"
#include "joint.hpp"
#include <sge/collision/world.hpp>
#include <sge/collision/optional_box.hpp>
#include <sge/collision/callback_signal.hpp>
#include <sge/collision/dim.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <ode/ode.h>
#include <map>
#include <utility>

namespace sge
{
namespace ode
{
class world
:
	public sge::collision::world
{
public:
	world(
		collision::optional_box const &,
		collision::constraint::type);
	
	signal::auto_connection
	register_test_callback(
		collision::test_callback const &);

	void
	test_callback_combiner(
		collision::test_callback_combiner const &);

	fcppt::signal::auto_connection
	register_begin_callback(
		collision::callback const &);

	fcppt::signal::auto_connection
	register_end_callback(
		collision::callback const &);

	collision::body_ptr const
	create_body(
		collision::satellite_ptr,
		collision::shapes::container const &,
		collision::point const &,
		collision::point const &);
	
	collision::shapes::sphere_ptr const
	create_sphere(
		collision::unit radius);

	collision::shapes::box_ptr const
	create_box(
		collision::dim const &);
	
	collision::group_ptr const 
	create_group();

	void
	update(
		collision::time_unit delta);

	void
	collides_with(
		collision::group_ptr,
		collision::group_ptr);

	~world();
private:
	// body needs the worldid and the plane joint
	friend class body;

	typedef
	std::map
	<
		std::pair
		<
			dBodyID,
			dBodyID
		>,
		bool
	> object_map;

	dWorldID const world_;
	dSpaceID space_;
	collision::callback_signal
		begin_signal_,
		end_signal_;
	fcppt::signal::object<collision::test_callback_fn>
		test_signal_;
	group_id group_id_;
	dReal time_remainder_;
	object_map collisions_;
	transformer transformer_;
	unsigned long body_count_;
	scoped_ptr<joint> plane_joint_;
	
	void step(
		dReal);
	void check_end_signals();
	group_id next_group_id();
	static void static_collide(
		void *,
		dGeomID,
		dGeomID);
	void collide(
		dGeomID,
		dGeomID);
	void call_signal(
		collision::callback_signal &,
		dBodyID,
		dBodyID);
	void destroy_body(
		dBodyID);
};
}
}

#endif
