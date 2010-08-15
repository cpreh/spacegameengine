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


#include "../group.hpp"
#include "../shapes/base.hpp"
#include "../log.hpp"
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/math/null.hpp>
#include <fcppt/text.hpp>

namespace
{
fcppt::log::object 
mylogger(
	fcppt::log::parameters::inherited(
		sge::bullet::log(),
		FCPPT_TEXT("group")));
}


sge::bullet::group::group(
	group_id const _category)
:
	category_(
		_category),
	collides_(
		fcppt::math::null<group_id>())
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("Created a new group with category ")
			<< category_);
}

void 
sge::bullet::group::add(
	collision::shapes::base_ptr const s)
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_ 
			<< FCPPT_TEXT("A shape of type ")
			<< typeid(*s).name()
			<< FCPPT_TEXT(" was added to group with category: ")
			<< category_);
	dynamic_cast<shapes::base &>(*s).add_to_group(
		*this);
}

void 
sge::bullet::group::collides_with(
	group &other)
{
	collides_ |= other.category_;
}

sge::bullet::group_id 
sge::bullet::group::category() const
{
	return 
		category_;
}

sge::bullet::group_id 
sge::bullet::group::collides() const
{
	return 
		collides_;
}
