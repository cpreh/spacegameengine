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
#ifndef SGE_COLLISION_WORLD_HPP_INCLUDED
#define SGE_COLLISION_WORLD_HPP_INCLUDED

#include <sge/collision/world_fwd.hpp>
#include <sge/collision/unit.hpp>
#include <sge/collision/point.hpp>
#include <sge/collision/callback.hpp>
#include <sge/collision/test_callback.hpp>
#include <sge/collision/satellite_fwd.hpp>
#include <sge/collision/time_unit.hpp>
#include <sge/collision/objects/circle_fwd.hpp>
#include <sge/signal/auto_connection.hpp>
#include <sge/export.hpp>
#include <sge/noncopyable.hpp>

namespace sge
{
namespace collision
{
class SGE_CLASS_SYMBOL world
{
	SGE_NONCOPYABLE(world)
protected:
	SGE_SYMBOL world();
public:
	virtual void
	test_callback(
		collision::test_callback const &) = 0;

	virtual signal::auto_connection
	register_callback(
		callback const &) = 0;
	
	virtual objects::circle_ptr const
	create_circle(
		satellite_ptr,
		point const &center,
		point const &speed,
		unit radius) = 0;

	virtual void
	update(
		time_unit delta) = 0;
	
	SGE_SYMBOL virtual ~world();
};
}
}

#endif
