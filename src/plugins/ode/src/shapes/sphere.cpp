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

#include "../../shapes/sphere.hpp"
#include "../../transformer.hpp"
#include "../../transformer_impl.hpp"

sge::ode::shapes::sphere::sphere(
	transformer const &_transformer,
	dSpaceID const _space,
	collision::unit const _radius)
:
	collision::shapes::sphere(),
	ode::shapes::base(
		dCreateSphere(
			_space,
			_transformer.unit_to_ode(
				_radius))),
	transformer_(
		_transformer)
{
}

sge::collision::unit sge::ode::shapes::sphere::radius() const
{
	return
		transformer_.unit_from_ode(
			dGeomSphereGetRadius(
				shape_));
}

void sge::ode::shapes::sphere::radius(
	collision::unit const _radius)
{
	dGeomSphereSetRadius(
		shape_,
		transformer_.unit_to_ode(
			_radius));
}
