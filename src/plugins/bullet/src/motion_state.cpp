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


#include "../motion_state.hpp"
#include "../conversion.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/output.hpp>

namespace
{
btTransform const make_transform(sge::bullet::point const &p)
{
	btTransform t;
	t.setIdentity();
	t.setOrigin(p);
	return t;
}
}

sge::bullet::motion_state::motion_state(change_callback const &_callback)
:
	pos_(
		make_transform(
			point(
				static_cast<unit>(0),
				static_cast<unit>(0),
				static_cast<unit>(0)
			)
		)
	),
	callback(_callback)
{
}

void sge::bullet::motion_state::pos(point const &v)
{
	//sge::cerr << "externally setting new position to: " << v.x() << "x" << v.y() << "x" << v.z() << "\n";
	pos_ = make_transform(v);
	callback(v);
}

sge::bullet::point const sge::bullet::motion_state::pos() const
{
	return pos_.getOrigin();
}

void sge::bullet::motion_state::getWorldTransform(btTransform &t) const
{
	t = pos_;
}

// called only by bullet internally
void sge::bullet::motion_state::setWorldTransform(btTransform const &t)
{
	//if (bullet_to_sge(t.getOrigin()) == sge::collision::point::null())
	//	sge::cerr << "bullet set new position to: " << bullet_to_sge(t.getOrigin()) << '\n';
	//pos_ = t;
	pos_ = make_transform(t.getOrigin());
	callback(pos_.getOrigin());
}
