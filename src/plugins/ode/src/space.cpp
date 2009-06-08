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


#include "../space.hpp"
#include <sge/math/rect/basic_impl.hpp>
#include <sge/optional_impl.hpp>

sge::ode::space::space(
	collision::optional_rect const &_rect)
:
	id_()
{
	if (!_rect)
	{
		id_ = dHashSpaceCreate(0);
	}
	else
	{
		collision::rect const r = *_rect;
		dVector3 center;
		center[0] = static_cast<dReal>(r.left() + r.w()/2);
		center[1] = static_cast<dReal>(r.top() + r.h()/2);
		center[2] = static_cast<dReal>(0);
		dVector3 extents;
		extents[0] = static_cast<dReal>(r.w());
		extents[1] = static_cast<dReal>(r.h());
		extents[2] = static_cast<dReal>(0);
		id_ = dQuadTreeSpaceCreate(
			0, 
			center, 
			extents, 
			8);
	}
}

dSpaceID &sge::ode::space::id()
{
	return id_;
}

dSpaceID const &sge::ode::space::id() const
{
	return id_;
}

sge::ode::space::~space()
{
	dSpaceDestroy(id_);
}
