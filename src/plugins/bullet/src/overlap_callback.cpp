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
#include "../overlap_callback.hpp"
#include "../types.hpp"
#include <bullet/BulletCollision/BroadphaseCollision/btBroadphaseProxy.h>

sge::bullet::overlap_callback::overlap_callback(
	collision::test_callback const &dispatch)
:
	dispatch(dispatch)
{
}

void sge::bullet::overlap_callback::reset(
	collision::test_callback const &_dispatch)
{
	dispatch = _dispatch;
}

bool sge::bullet::overlap_callback::needBroadphaseCollision(
	btBroadphaseProxy * const a,
	btBroadphaseProxy * const b) const
{
	return dispatch(
		*static_cast<collision::satellite const *>(
			static_cast<body_type *>(a->m_clientObject)->getUserPointer()),
		*static_cast<collision::satellite const *>(
			static_cast<body_type *>(b->m_clientObject)->getUserPointer())
		);
}
