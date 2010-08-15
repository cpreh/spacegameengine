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


#include "../../shapes/base.hpp"
#include "../../group.hpp"
#include <sge/collision/shape_ambiguity.hpp>

sge::ode::shapes::base::base(
	dGeomID const _shape)
:
	shape_(
		_shape)
{
	dGeomSetCategoryBits(
		shape_,
		static_cast<group_id>(
			0));
	dGeomSetCollideBits(
		shape_,
		static_cast<group_id>(
			0));
}

void sge::ode::shapes::base::assign_body(
	dBodyID const _body)
{
	if (dGeomGetBody(shape_))
		throw collision::shape_ambiguity();
	dGeomSetBody(
		shape_,
		_body);
}

void sge::ode::shapes::base::add_to_group(
	group const &_group)
{
	/*sge::cerr
		<< "shape: i should be added to the group with category "
		<< _group.category()
		<< " and collides "
		<< _group.collides()
		<< ", my own category is "
		<< dGeomGetCategoryBits(shape_)
		<< " and my own collides is "
		<< dGeomGetCollideBits(shape_) << "\n";*/
	dGeomSetCategoryBits(
		shape_,
		dGeomGetCategoryBits(shape_) | _group.category());
	dGeomSetCollideBits(
		shape_,
		dGeomGetCollideBits(shape_) | _group.collides());
		/*
	sge::cerr
		<< "shape: aftermath "
		<< ", my own category is "
		<< dGeomGetCategoryBits(shape_)
		<< " and my own collides is "
		<< dGeomGetCollideBits(shape_) << "\n";*/
}

sge::ode::shapes::base::~base()
{
	// TODO: delete shape from body-shape-container here
	dGeomDestroy(
		shape_);
}
