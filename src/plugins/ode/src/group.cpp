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
#include "../body.hpp"
#include <fcppt/math/null.hpp>
#include <fcppt/assert_message.hpp>
#include <fcppt/text.hpp>

sge::ode::group::group(
	group_id const _category)
:
	category_(
		_category),
	collides_(
		fcppt::math::null<group_id>()),
	dirty_(false)
{
}

void
sge::ode::group::add(
	collision::shapes::base_ptr const _body
)
{
// FIXME!
#if 0
	dirty_ =
		true;
	dynamic_cast<body &>(
		*_body
	).add_to_group(
		*this
	);
#endif
}

void sge::ode::group::collides_with(
	group const &other)
{
	FCPPT_ASSERT_MESSAGE(!dirty_ && !other.dirty_,FCPPT_TEXT("Constraint violation: Tried to change a group which already has shapes in it"));
	collides_ |= other.category();
}

sge::ode::group_id sge::ode::group::category() const
{
	return category_;
}

sge::ode::group_id sge::ode::group::collides() const
{
	return collides_;
}
