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
#ifndef SGE_BULLET_OBJECT_HPP_INCLUDED
#define SGE_BULLET_OBJECT_HPP_INCLUDED

#include "types.hpp"
#include "world_fwd.hpp"
#include "constraint.hpp"
#include "motion_state.hpp"
#include <sge/collision/point.hpp>
#include <sge/collision/unit.hpp>
#include <sge/collision/satellite_fwd.hpp>
#include <sge/math/vector/basic_decl.hpp>

namespace sge
{
namespace bullet
{
class object
{
public:
	object(
		world &,
		collision::satellite_ptr,
		shape_ptr,
		unit mass);

	void pos(collision::point const &);
	collision::point const pos() const;
	void speed(collision::point const &);
	collision::point const speed() const;
	~object();
private:
	friend class motion_state;
	void position_changed(point const &);

	collision::satellite_ptr sat;
	world_type &world_;
	shape_ptr shape_;
	motion_state motion_state_;
	body_type body_;
	constraint constraint_;
};
}
}

#endif
