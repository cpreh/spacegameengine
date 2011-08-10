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


#include "is_solid.hpp"
#include <sge/projectile/body/solidity/nonsolid.hpp>
#include <fcppt/variant/apply_unary.hpp>

namespace
{
class is_solid_visitor
{
public:
	typedef bool result_type;

	result_type
	operator()(
		sge::projectile::body::solidity::nonsolid const &) const
	{
		return false;
	}

	template<typename T>
	result_type
	operator()(
		T const &) const
	{
		return true;
	}
};
}

bool
sge::projectile::body::solidity::is_solid(
	variant const &v)
{
	return
		fcppt::variant::apply_unary(
			is_solid_visitor(),
			v);
}
