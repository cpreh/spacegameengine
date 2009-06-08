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


#ifndef SGE_BULLET_WORLD_HPP_INCLUDED
#define SGE_BULLET_WORLD_HPP_INCLUDED

#include "types.hpp"
#include "overlap_callback.hpp"
#include <sge/collision/world.hpp>
#include <sge/scoped_ptr.hpp>

namespace sge
{
namespace bullet
{
class world : public collision::world
{
public:
	world();

	void test_callback(
		collision::test_callback const &);

	signal::auto_connection
	register_callback(
		collision::callback const &);

	collision::objects::circle_ptr const
	create_circle(
		collision::satellite_ptr,
		collision::point const &center,
		collision::point const &speed,
		collision::unit);

	void update(
		collision::time_unit delta);

	world_type &world_internal();
	body_type &zero_body();
	~world();
private:
	collision::test_callback test_;
	collision::callback_signal callback_signal_;

	scoped_ptr<configuration_type> configuration;
	scoped_ptr<dispatcher_type> dispatcher;
	scoped_ptr<broadphase_type> broadphase;
	scoped_ptr<constraint_solver_type> constraint_solver;
	overlap_callback overlap_callback_;
	scoped_ptr<world_type> world_;
	body_type zero_body_;
};
}
}

#endif
