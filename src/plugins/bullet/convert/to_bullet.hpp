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


#ifndef SGE_BULLET_CONVERT_TO_BULLET_HPP_INCLUDED
#define SGE_BULLET_CONVERT_TO_BULLET_HPP_INCLUDED

#include "../point.hpp"
#include "../dim.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <LinearMath/btVector3.h>

namespace sge
{
namespace bullet
{
namespace convert
{
inline btVector3 const 
to_bullet(
	point const &p)
{
	return
		btVector3(
			p.x(),
			p.y(),
			p.z());
}

inline btVector3 const 
to_bullet(
	dim const &p)
{
	return
		btVector3(
			p.w(),
			p.h(),
			p.d());
}
}
}
}

#endif
