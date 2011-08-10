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


#include "extract_mass.hpp"
#include <fcppt/variant/apply_unary.hpp>

namespace
{
struct mass_visitor
{
public:
	typedef
	btScalar
	result_type;

	result_type
	operator()(
		sge::projectile::body::solidity::solid const &s) const
	{
		return s.mass().get();
	}

	result_type
	operator()(
		sge::projectile::body::solidity::static_ const &) const
	{
		return
			static_cast<btScalar>(
				0);
	}

	result_type
	operator()(
		sge::projectile::body::solidity::nonsolid const &) const
	{
		return
			static_cast<btScalar>(
				1);
	}
};
}

btScalar
sge::projectile::body::solidity::extract_mass(
	variant const &v)
{
	return
		fcppt::variant::apply_unary(
			mass_visitor(),
			v);
}
