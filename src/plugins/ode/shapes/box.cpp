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


#include "../../shapes/box.hpp"
#include "../../point.hpp"
#include "../../transformer.hpp"
#include "../../transformer_impl.hpp"
#include "../../dim.hpp"
#include <sge/math/dim/basic_impl.hpp>

sge::ode::shapes::box::box(
	transformer const &_transformer,
	dSpaceID const _space,
	collision::dim const &_dim)
:
	collision::shapes::box(),
	ode::shapes::base(
		dCreateBox(
			_space,
			_transformer.dim_to_ode(
				_dim).w(),
			_transformer.dim_to_ode(
				_dim).h(),
			static_cast<dReal>(
				1))),
	transformer_(
		_transformer)
{
	//sge::cerr << "created a box " << this << " with radius " << _radius << "\n";
}

sge::collision::dim const
sge::ode::shapes::box::dim() const
{
	dVector3 result;
	dGeomBoxGetLengths(
		shape_,
		result);
	return 
		transformer_.dim_from_ode(
			sge::ode::dim(
				result[0],
				result[1],
				result[2]));
}

void 
sge::ode::shapes::box::dim(
	collision::dim const &_dim)
{
	//sge::cerr << "set radius to " << this << " with radius " << _radius << "\n";
	sge::ode::dim const o =
		transformer_.dim_to_ode(
			_dim);
	dGeomBoxSetLengths(
		shape_,
		o.w(),
		o.h(),
		o.d());
}
