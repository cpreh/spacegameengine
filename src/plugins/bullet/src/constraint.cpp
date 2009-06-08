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


#include "../constraint.hpp"

sge::bullet::constraint::constraint(
	world_type &world,
	body_type &body,
	body_type &zero_body)
:
	world(world),
	constraint_(
		body,
		zero_body,
		btTransform::getIdentity(),
		btTransform::getIdentity(),
		false)
{
	// Use limit(axis, a, b) where a>b to disable limits on that axis
	constraint_.setLimit(0,1,0); // Disable X axis limits
	constraint_.setLimit(1,1,0); // Disable Y axis limits
	constraint_.setLimit(2,0,0); // Set the Z axis to always be equal to zero
	constraint_.setLimit(3,1,0); // Uncap the rotational axes
	constraint_.setLimit(4,1,0); // Uncap the rotational axes
	constraint_.setLimit(5,1,0); // Uncap the rotational axes

	world.addConstraint(&constraint_);
}

sge::bullet::constraint::~constraint()
{
	world.removeConstraint(&constraint_);
}
