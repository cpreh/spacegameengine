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
#include "../../convert/to_bullet.hpp"
#include "../../convert/dim_to_sge.hpp"
#include "../../log.hpp"
#include <sge/exception.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/text.hpp>

namespace
{
fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("shapes: box")));
}

sge::bullet::shapes::box::box(
	collision::satellite_ptr _satellite,
	collision::constraint::type _constraint,
	sge::bullet::world &_world,
	collision::point const &_position,
	collision::solidity::type const _solidity,
	collision::dim const &_dim)
:
	base(
		bullet_shape_ptr(
			new btBoxShape(
				// btBoxShape wants _halfdimensions_, so 1/2 here
				convert::to_bullet(
					_dim/
					static_cast<unit>(2)))),
		_satellite,
		_constraint,
		_world,
		_position,
		_solidity)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Added a box with halfdimensions: ")
			<< (_dim/static_cast<unit>(2)));
			
}

sge::collision::dim const 
sge::bullet::shapes::box::dim() const
{
	return 
		convert::dim_to_sge(
			// NOTE: what margin? collision margin?
			dynamic_cast<btBoxShape &>(*shape_).getHalfExtentsWithoutMargin()); 
}

void 
sge::bullet::shapes::box::dim(
	collision::dim const &)
{
	throw 
		sge::exception(
			FCPPT_TEXT("changing the dimensions of a box dynamically is not supported by bullet-2.75 (last version checked)"));
}
