/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../../shapes/sphere.hpp"
#include "../../log.hpp"
#include <sge/collision/satellite.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/text.hpp>

namespace
{
fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("shapes: sphere")));
}


sge::bullet::shapes::sphere::sphere(
	collision::satellite_ptr _satellite,
	collision::constraint::type const _constraint,
	sge::bullet::world &_world,
	unit const _radius,
	collision::solidity::type const _solidity,
	collision::point const &_position)
:
	base(
		bullet_shape_ptr(
			new btSphereShape(
				_radius)),
		move(
			_satellite
		),
		_constraint,
		_world,
		_position,
		_solidity)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Added a sphere with radius: ")
			<< _radius);
}

sge::collision::unit 
sge::bullet::shapes::sphere::radius() const
{
	return 
		dynamic_cast<btSphereShape &>(*shape_).getRadius();
}

void 
sge::bullet::shapes::sphere::radius(
	collision::unit const _radius)
{ 
	// I don't know why it's called "unscaled" radius but it 
	// does the same as the constructor (in bullet-2.75)
	dynamic_cast<btSphereShape &>(*shape_).setUnscaledRadius(
		_radius);
}
