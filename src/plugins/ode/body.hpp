/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_ODE_BODY_HPP_INCLUDED
#define SGE_ODE_BODY_HPP_INCLUDED

#include "world_fwd.hpp"
#include "transformer_fwd.hpp"
#include "group_id.hpp"
#include "shapes/container.hpp"
#include <sge/collision/body.hpp>
#include <sge/collision/shapes/container.hpp>
#include <sge/collision/satellite_ptr.hpp>
#include <ode/ode.h>
#include "group.hpp"

namespace sge
{
namespace ode
{
class body
:
	public sge::collision::body
{
public:
	body(
		world &,
		transformer const &,
		dWorldID,
		collision::satellite_ptr,
		collision::shapes::container const &,
		collision::point const &,
		collision::point const &);
	collision::point const position() const;
	void position(
		collision::point const &);
	collision::point const linear_velocity() const;
	void linear_velocity(
		collision::point const &);
	bool is_active();
	void is_active(
		bool);
	void add_to_group(
		group &);
	~body();
private:
	// world needs to access the satellite in its collision function
	friend class world;

	world &world_;
	transformer const &transformer_;
	dBodyID body_;
	collision::satellite_ptr satellite_;
	shapes::container shapes_;

	void add(
		collision::shapes::base_ptr);
	static void moved(
		dBodyID);
};
}
}

#endif
